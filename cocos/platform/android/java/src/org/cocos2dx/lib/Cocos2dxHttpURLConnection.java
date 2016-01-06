/****************************************************************************
Copyright (c) 2010-2014 cocos2d-x.org

http://www.cocos2d-x.org

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
import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.security.KeyStore;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Map.Entry;
import java.util.zip.GZIPInputStream;
import java.util.zip.InflaterInputStream;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManagerFactory;

public class Cocos2dxHttpURLConnection
{
    private static final String POST_METHOD = "POST" ;
    private static final String PUT_METHOD = "PUT" ;

    static HttpURLConnection createHttpURLConnection(String linkURL) {
        URL url;
        HttpURLConnection urlConnection;
        try {
            url = new URL(linkURL);
            urlConnection = (HttpURLConnection) url.openConnection();
            //Accept-Encoding
            urlConnection.setRequestProperty("Accept-Encoding", "identity");
            urlConnection.setDoInput(true);
        } catch (Exception e) {
            Log.e("URLConnection exception", e.toString());
            return null;
        }

        return urlConnection;
    }

    static void setReadAndConnectTimeout(HttpURLConnection urlConnection, int readMiliseconds, int connectMiliseconds) {
        urlConnection.setReadTimeout(readMiliseconds);
        urlConnection.setConnectTimeout(connectMiliseconds);
    }

    static void setRequestMethod(HttpURLConnection urlConnection, String method){
        try {
            urlConnection.setRequestMethod(method);
            if(method.equalsIgnoreCase(POST_METHOD) || method.equalsIgnoreCase(PUT_METHOD)) {
                urlConnection.setDoOutput(true);
            }
        } catch (ProtocolException e) {
            Log.e("URLConnection exception", e.toString());
        }

    }

    static void setVerifySSL(HttpURLConnection urlConnection, String sslFilename) {
        if(!(urlConnection instanceof HttpsURLConnection))
            return;
        

        HttpsURLConnection httpsURLConnection = (HttpsURLConnection)urlConnection;

        try {
            InputStream caInput = null;
            if (sslFilename.startsWith("/")) {
                caInput = new BufferedInputStream(new FileInputStream(sslFilename));
            }else {
                String assetString = "assets/";
                String assetsfilenameString = sslFilename.substring(assetString.length());
                caInput = new BufferedInputStream(Cocos2dxHelper.getActivity().getAssets().open(assetsfilenameString));
            }

            CertificateFactory cf = CertificateFactory.getInstance("X.509");
            Certificate ca;
            ca = cf.generateCertificate(caInput);
            System.out.println("ca=" + ((X509Certificate) ca).getSubjectDN());
            caInput.close();

            // Create a KeyStore containing our trusted CAs
            String keyStoreType = KeyStore.getDefaultType();
            KeyStore keyStore = KeyStore.getInstance(keyStoreType);
            keyStore.load(null, null);
            keyStore.setCertificateEntry("ca", ca);

            // Create a TrustManager that trusts the CAs in our KeyStore
            String tmfAlgorithm = TrustManagerFactory.getDefaultAlgorithm();
            TrustManagerFactory tmf = TrustManagerFactory.getInstance(tmfAlgorithm);
            tmf.init(keyStore);

            // Create an SSLContext that uses our TrustManager
            SSLContext context = SSLContext.getInstance("TLS");
            context.init(null, tmf.getTrustManagers(), null);

            httpsURLConnection.setSSLSocketFactory(context.getSocketFactory());
        } catch (Exception e) {
            Log.e("URLConnection exception", e.toString());
        }
    }

    //Add header
    static void addRequestHeader(HttpURLConnection urlConnection, String key, String value) {
        urlConnection.setRequestProperty(key, value);
    }

    static int connect(HttpURLConnection http) {
        int suc = 0;

        try {
            http.connect();
        } catch (IOException e) {
            Log.e("cocos2d-x debug info", "come in connect");
            Log.e("cocos2d-x debug info", e.toString());
            suc = 1;
        }

        return suc;
    }

    static void disconnect(HttpURLConnection http) {
        http.disconnect();
    }

    static void sendRequest(HttpURLConnection http, byte[] byteArray) {
        try {
            OutputStream out = http.getOutputStream();
            if(null !=  byteArray) {
                out.write(byteArray);
                out.flush();
            }
            out.close();
        } catch (IOException e) {
            Log.e("URLConnection exception", e.toString());
        }
    }

    static String getResponseHeaders(HttpURLConnection http) {
        Map<String, List<String>> headers = http.getHeaderFields();
        if (null == headers) {
            return null;
        }

        String header = "";

        for (Entry<String, List<String>> entry: headers.entrySet()) {
            String key = entry.getKey();
            if (null == key) {
                header += listToString(entry.getValue(), ",") + "\n";
            } else {
                header += key + ":" + listToString(entry.getValue(), ",") + "\n";
            }
        }

        return header;
    }

    static String getResponseHeaderByIdx(HttpURLConnection http, int idx) {
        Map<String, List<String>> headers = http.getHeaderFields();
        if (null == headers) {
            return null;
        }

        String header = null;

        int counter = 0;
        for (Entry<String, List<String>> entry: headers.entrySet()) {
            if (counter == idx) {
                String key = entry.getKey();
                if (null == key) {
                    header = listToString(entry.getValue(), ",") + "\n";
                } else {
                    header = key + ":" + listToString(entry.getValue(), ",") + "\n";
                }
                break;
            }
            counter++;
        }

        return header;
    }

    static String getResponseHeaderByKey(HttpURLConnection http, String key) {
        if (null == key) {
            return null;
        }

        Map<String, List<String>> headers = http.getHeaderFields();
        if (null == headers) {
            return null;
        }

        String header = null;

        for (Entry<String, List<String>> entry: headers.entrySet()) {
            if (key.equalsIgnoreCase(entry.getKey())) {
                if ("set-cookie".equalsIgnoreCase(key)) {
                    header = combinCookies(entry.getValue(), http.getURL().getHost());
                } else {
                    header = listToString(entry.getValue(), ",");
                }
                break;
            }
        }

        return header;
    }

    static int getResponseHeaderByKeyInt(HttpURLConnection http, String key) {
        String value = http.getHeaderField(key);

        if (null == value) {
            return 0;
        } else {
            return Integer.parseInt(value);
        }
    }

    static byte[] getResponseContent(HttpURLConnection http) {
        InputStream in;
        try {            
            in = http.getInputStream();
            String contentEncoding = http.getContentEncoding();
            if (contentEncoding != null) {
                if(contentEncoding.equalsIgnoreCase("gzip")){
                    in = new GZIPInputStream(http.getInputStream()); //reads 2 bytes to determine GZIP stream!
                }
                else if(contentEncoding.equalsIgnoreCase("deflate")){
                    in = new InflaterInputStream(http.getInputStream());
                }
            }       
        } catch (IOException e) {
            in = http.getErrorStream();
        } catch (Exception e) {
            Log.e("URLConnection exception", e.toString());
            return null;
        }

        try {
            byte[] buffer = new byte[1024];
            int size   = 0;
            ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
            while((size = in.read(buffer, 0 , 1024)) != -1)
            {
                bytestream.write(buffer, 0, size);
            }
            byte retbuffer[] = bytestream.toByteArray();
            bytestream.close();
            return retbuffer;
        } catch (Exception e) {
            Log.e("URLConnection exception", e.toString());
        }

        return null;
    }
    
    static int getResponseCode(HttpURLConnection http) {
        int code = 0;
        try {
            code = http.getResponseCode();
        } catch (IOException e) {
            Log.e("URLConnection exception", e.toString());
        }
        return code;
    }

    static String getResponseMessage(HttpURLConnection http) {
        String msg;
        try {
            msg = http.getResponseMessage();
        } catch (IOException e) {
            msg = e.toString();
            Log.e("URLConnection exception", msg);
        }

        return msg;
    }

    public static String listToString(List<String> list, String strInterVal) {
        if (list == null) {
            return null;
        }
        StringBuilder result = new StringBuilder();
        boolean flag = false;
        for (String str : list) {
            if (flag) {
                result.append(strInterVal);
            }
            if (null == str) {
                str = "";
            }
            result.append(str);
            flag = true;
        }
        return result.toString();
    }

    public static String combinCookies(List<String> list, String hostDomain) {
        StringBuilder sbCookies = new StringBuilder();
        String domain    = hostDomain;
        String tailmatch = "FALSE";
        String path      = "/";
        String secure    = "FALSE";
        String key = null;
        String value = null;
        String expires = null;
        for (String str : list) {
            String[] parts = str.split(";");
            for (String part : parts) {
                int firstIndex = part.indexOf("=");
                if (-1 == firstIndex)
                    continue;

                String[] item =  {part.substring(0, firstIndex), part.substring(firstIndex + 1)};
                if ("expires".equalsIgnoreCase(item[0].trim())) {
                    expires = str2Seconds(item[1].trim());
                } else if("path".equalsIgnoreCase(item[0].trim())) {
                    path = item[1];
                } else if("secure".equalsIgnoreCase(item[0].trim())) {
                    secure = item[1];
                } else if("domain".equalsIgnoreCase(item[0].trim())) {
                    domain = item[1];
                } else if("version".equalsIgnoreCase(item[0].trim()) || "max-age".equalsIgnoreCase(item[0].trim())) {
                    //do nothing
                } else {
                    key = item[0];
                    value = item[1];
                }
            }

            if (null == domain) {
                domain = "none";
            }

            sbCookies.append(domain);
            sbCookies.append('\t');
            sbCookies.append(tailmatch);  //access
            sbCookies.append('\t');
            sbCookies.append(path);      //path
            sbCookies.append('\t');
            sbCookies.append(secure);    //secure
            sbCookies.append('\t');
            sbCookies.append(expires);   //expires
            sbCookies.append("\t");
            sbCookies.append(key);       //key
            sbCookies.append("\t");
            sbCookies.append(value);     //value
            sbCookies.append('\n');
        }

        return sbCookies.toString();
    }

    private static String str2Seconds(String strTime) {
        Calendar c = Calendar.getInstance();
        long millisSecond = 0;

        try {
            c.setTime(new SimpleDateFormat("EEE, dd-MMM-yy hh:mm:ss zzz", Locale.US).parse(strTime));
            millisSecond = c.getTimeInMillis()/1000;
        } catch (ParseException e) {
            Log.e("URLConnection exception", e.toString());
        }

        return Long.toString(millisSecond);
    }
}
