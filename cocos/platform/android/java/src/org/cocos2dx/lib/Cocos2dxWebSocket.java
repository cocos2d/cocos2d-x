/****************************************************************************
 Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.
 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

package org.cocos2dx.lib;

import android.util.Log;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.ConnectException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.security.KeyManagementException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.SecureRandom;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

import javax.net.ssl.KeyManager;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.TrustManagerFactory;
import javax.net.ssl.X509TrustManager;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.WebSocket;
import okhttp3.WebSocketListener;
import okio.ByteString;

@SuppressWarnings("unused")
public class Cocos2dxWebSocket {

    private static final int CONNECT_TIMEOUT = 40;
    private static final int READ_TIMEOUT = 40;
    private static final int WRITE_TIMEOUT = 40;

    private static WebSocketClientRC __defaultClient = null;

    private static AtomicLong __connectionIdGenerator = new AtomicLong(10000);

    private static Map<Long, WebSocketAdapter> __socketCache = new ConcurrentHashMap<>();

    private static Map<String, WebSocketClientRC> __secureClientCache = new ConcurrentHashMap<>();

    /**
     * OkHttpClient adapter with reference counting.
     * Terminate client when _refCount reach 0
     */
    private static final class WebSocketClientRC {
        WebSocketClientRC(OkHttpClient client, boolean defaultClient) {
            this._wsClient = client;
            this._refCount = 0;
            this._isDefaultClient = defaultClient;
        }

        synchronized void retain() {
            this._refCount++;
        }

        synchronized void release() {
            this._refCount--;
            if(this._refCount<= 0) {
                this.shutdown();
            }
        }

        private void shutdown() {
            if(this._wsClient !=null) {
                this._wsClient.dispatcher().executorService().shutdown();
                for(String key : __secureClientCache.keySet()) {
                    if(__secureClientCache.get(key) == this) {
                        __secureClientCache.remove(key);
                    }
                }
                this._wsClient = null;
            }
        }

        OkHttpClient getWSClient() {
            return _wsClient;
        }

        private OkHttpClient _wsClient;
        private int _refCount;
        private boolean _isDefaultClient;
    }

    private static final class WebSocketAdapter {

        WebSocketAdapter(WebSocket socket, WebSocketClientRC client) {
            this._socket = socket;
            this._client = client;
        }

        public void close(boolean syncClose)
        {
            this._closed = true; //to prevent callbacks from executing after close
            this._syncClose = syncClose;
            this._socket.close(1000, "manually close by client");
        }

        public void send(String text) {
            this._socket.send(text);
        }

        public void send(ByteString binary)
        {
            this._socket.send(binary);
        }

        private WebSocket _socket;
        private boolean _syncClose = false;
        private boolean _closed = false;
        private WebSocketClientRC _client;

    }

    private static final class WebSocketListenerImpl extends WebSocketListener {

        private long _connectionID;

        WebSocketListenerImpl(long cid) {
            this._connectionID = cid;
        }

        @Override
        public void onOpen(WebSocket webSocket, Response response) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);
            if(socket != null && socket._closed) return;
            triggerEventInGLThread(_connectionID, "open", response.message(), false);
        }

        @Override
        public void onMessage(WebSocket webSocket, String text) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);
            if(socket != null && socket._closed) return;

            triggerEventInGLThread(_connectionID, "message", text, false);
        }

        @Override
        public void onMessage(WebSocket webSocket, ByteString bytes) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);
            if(socket != null && socket._closed) return;
            triggerEventInGLThread(_connectionID, "message", bytes.toString(), true);
        }

        @Override
        public void onClosing(WebSocket webSocket, int code, String reason) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);
            if(socket != null && socket._closed) return;
            triggerEventInGLThread(_connectionID, "closing", reason, false);
        }

        @Override
        public void onClosed(WebSocket webSocket, int code, String reason) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);
            if(socket != null && socket._syncClose) {
                //This procedure DOES NOT run in GL thread, so that this message will not be blocked
                //in task queue.
                triggerEvent(_connectionID, "sync-closed", "", false);
            }else {
                triggerEventInGLThread(_connectionID, "_closed", reason, false);
            }

            if(socket != null) {
                socket._client.release();
            }
            __socketCache.remove(_connectionID);
        }

        @Override
        public void onFailure(WebSocket webSocket, Throwable t, Response response) {
            WebSocketAdapter socket = __socketCache.get(_connectionID);

            if(t instanceof UnknownHostException) {
                triggerEventInGLThread(_connectionID, "error", "CONNECTION_FAILURE", false);
            } else if (t instanceof  SocketTimeoutException) {
                triggerEventInGLThread(_connectionID, "error", "TIME_OUT", false);
            } else if (t instanceof ConnectException) {
                triggerEventInGLThread(_connectionID, "error", "CONNECTION_FAILURE", false);
            } else {
                triggerEventInGLThread(_connectionID, "error", t.getMessage(), false);
            }
            if(socket != null) {
                socket._client.release();
            }
            __socketCache.remove(_connectionID);
        }
    }

    /**
     * Setup WebSocket builder with default parameters
     * @return
     */
    private static okhttp3.OkHttpClient.Builder defaultWSClientBuilder() {
        OkHttpClient.Builder builder = new OkHttpClient.Builder();
        builder.connectTimeout(CONNECT_TIMEOUT, TimeUnit.SECONDS)
                .readTimeout(READ_TIMEOUT, TimeUnit.SECONDS)
                .writeTimeout(WRITE_TIMEOUT, TimeUnit.SECONDS);
        return builder;
    }

    /**
     * Get the default OkHttpClient which will use system SSL context
     * @return
     */
    private static WebSocketClientRC getDefaultClient() {
        if(__defaultClient == null) {
            OkHttpClient client = defaultWSClientBuilder().build();
            __defaultClient = new WebSocketClientRC(client, true);
            __defaultClient.retain(); //prevent shutdown by default
        }
        return __defaultClient;
    }

    /**
     * Setup the SSL context for client builder with provided CA file content
     * @param caContent
     * @param builder
     * @return
     */
    private static OkHttpClient.Builder configSSL(String caContent, OkHttpClient.Builder builder)  {
        if(caContent == null || caContent.isEmpty()) return null;
        ByteArrayInputStream is = null;
        BufferedInputStream bis = null;
        try {
            KeyStore ks = KeyStore.getInstance(KeyStore.getDefaultType());
            ks.load(null, null);

            is = new ByteArrayInputStream(caContent.getBytes());
            bis = new BufferedInputStream(is);

            CertificateFactory cff;

            //The default provider may cause parse exception,
            //choose provider "BC" by default
            try {
                cff =  CertificateFactory.getInstance("X.509", "BC");
            } catch (NoSuchProviderException e) {
                e.printStackTrace();
                cff =  CertificateFactory.getInstance("X.509");
            }


            while(bis.available() > 0) {
                X509Certificate ce = (X509Certificate)cff.generateCertificate(bis);
                String alias = ce.getSubjectX500Principal().getName();
                ks.setCertificateEntry(alias, ce);
            }

            TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
            tmf.init(ks);
            TrustManager[] trustManagers = tmf.getTrustManagers();

            KeyManagerFactory kmf = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());
            kmf.init(ks, null);
            KeyManager[] keyManagers = kmf.getKeyManagers();

            SSLContext ctx = SSLContext.getInstance("TLS");
            ctx.init(keyManagers, trustManagers, new SecureRandom());

            builder.sslSocketFactory(ctx.getSocketFactory(), (X509TrustManager)trustManagers[0]);
            return builder;
        } catch (KeyStoreException e) {
            e.printStackTrace();
        } catch (CertificateException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (UnrecoverableKeyException e) {
            e.printStackTrace();
        } catch (KeyManagementException e) {
            e.printStackTrace();
        } finally {
            if(is!=null) {
                try {
                    is.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if(bis != null) {
                try {
                    bis.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    public static long connect(String url, String[] protocals, String caContent) {
        Request.Builder requestBuilder = new Request.Builder();

        //add protocol list to header
        if(protocals != null && protocals.length > 0) {
            //join string
            StringBuilder buffer = new StringBuilder();
            for(int i = 0; i < protocals.length - 1; i ++) {
                buffer.append(protocals[i]);
                buffer.append("; ");
            }
            buffer.append(protocals[protocals.length - 1]);
            requestBuilder.addHeader("Sec-WebSocket-Protocol", buffer.toString());
        }

        OkHttpClient.Builder clientBuilder = null;
        WebSocketClientRC client = null;

        if(caContent != null && !caContent.isEmpty()) {
            // use existing WebSocket client if exists
            if(__secureClientCache.containsKey(caContent) ){
                client = __secureClientCache.get(caContent);
            }else {
                clientBuilder = defaultWSClientBuilder();
                clientBuilder = configSSL(caContent, clientBuilder);
                if (clientBuilder != null) {
                    client = new WebSocketClientRC(clientBuilder.build(), false);
                    __secureClientCache.put(caContent, client);
                }
            }
        }

        if(client == null){
            client = getDefaultClient();
        }

        long connectionId = __connectionIdGenerator.incrementAndGet();
        Request request = requestBuilder.url(url).build();

        WebSocketListenerImpl listener = new WebSocketListenerImpl(connectionId);
        WebSocket wsSocket = client.getWSClient().newWebSocket(request, listener);
        __socketCache.put(connectionId, new WebSocketAdapter(wsSocket, client));

        client.retain();

        return connectionId;
    }

    public static void disconnect(long connectionID, boolean syncClose) {
        WebSocketAdapter socket = __socketCache.get(connectionID);
        if(socket != null) {
            socket.close(syncClose);
        }else {
            Log.e("[WebSocket]", "_socket "+connectionID + " not found!");
        }
    }

    public static void sendBinary(long connectionID, byte[] message)
    {
        WebSocketAdapter socket = __socketCache.get(connectionID);
        if(socket != null) {
            socket.send(ByteString.of(message));
        }else {
            Log.e("[WebSocket]", "_socket "+connectionID + " not found!");
        }
    }

    public static void sendString(long connectionID, String message)
    {
        WebSocketAdapter socket = __socketCache.get(connectionID);
        if(socket != null) {
            socket.send(message);
        }else {
            Log.e("[WebSocket]", "_socket "+connectionID + " not found!");
        }
    }

    private static void triggerEventInGLThread(final long connectionID, final String eventName, final String data, final boolean isBinary)
    {
        ((Cocos2dxActivity)Cocos2dxHelper.getActivity()).runOnGLThread(new Runnable() {
            @Override
            public void run() {
                triggerEvent(connectionID, eventName, data, isBinary);
            }
        });

    }

    static native void triggerEvent(long connectionID, String eventName, String data, boolean isBinary);

}
