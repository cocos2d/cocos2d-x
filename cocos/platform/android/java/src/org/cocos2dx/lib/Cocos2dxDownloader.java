/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

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

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class Cocos2dxDownloader {

    private int _id;
    private OkHttpClient _httpClient = null;

    private String _tempFileNameSuffix;
    private int _countOfMaxProcessingTasks;
    private ConcurrentHashMap<Integer,Call> _taskMap = new ConcurrentHashMap<>();
    private Queue<Runnable> _taskQueue = new LinkedList<>();
    private int _runningTaskCount = 0;
    private static ConcurrentHashMap<String, Boolean> _resumingSupport = new ConcurrentHashMap<>();

    private enum ErrorCode{
        ERROR_NO_ERROR(0),
        ERROR_INVALID_PARAMS(-1),
        ERROR_FILE_OP_FAILED(-2),
        ERROR_IMPL_INTERNAL(-3);
        private final int value;

        ErrorCode(int v) {
            this.value = v;
        }

        public int getValue() {return value;}
    }

    private void onProgress(final int id, final long downloadBytes, final long downloadNow, final long downloadTotal) {
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnProgress(_id, id, downloadBytes, downloadNow, downloadTotal);
            }
        });
    }

    private void onFinish(final int id, final ErrorCode errCode, final String errStr, final byte[] data) {
        Call task =_taskMap.get(id);
        if (null == task) return;
        _taskMap.remove(id);
        _runningTaskCount -= 1;
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnFinish(_id, id, errCode.getValue(), errStr, data);
            }
        });
        runNextTaskIfExists();
    }

    public static Cocos2dxDownloader createDownloader(int id, int timeoutInSeconds, String tempFileSuffix, int maxProcessingTasks) {
        Cocos2dxDownloader downloader = new Cocos2dxDownloader();
        downloader._id = id;

        if (timeoutInSeconds > 0) {
            downloader._httpClient = new OkHttpClient().newBuilder()
                    .followRedirects(true)
                    .followSslRedirects(true)
                    .callTimeout(timeoutInSeconds, TimeUnit.SECONDS)
                    .build();
        } else {
            downloader._httpClient = new OkHttpClient().newBuilder()
                    .followRedirects(true)
                    .followSslRedirects(true)
                    .build();
        }


        downloader._tempFileNameSuffix = tempFileSuffix;
        downloader._countOfMaxProcessingTasks = maxProcessingTasks;
        return downloader;
    }

    public static void createTask(final Cocos2dxDownloader downloader, int id_, String url_, String path_, String []header_) {
        final int id = id_;
        final String url = url_;
        final String path = path_;
        final String[] header = header_;

        Runnable taskRunnable = new Runnable() {
            String domain = null;
            String host = null;
            File tempFile = null;
            File finalFile = null;
            long downloadStart = 0;

            @Override
            public void run() {
                Call task = null;

                do {
                    if (path.length() > 0) {
                        try {
                            URI uri = new URI(url);
                            domain = uri.getHost();
                        } catch (URISyntaxException e) {
                            e.printStackTrace();
                            break;
                        } catch (NullPointerException e) {
                            e.printStackTrace();
                            break;
                        }

                        // file task
                        tempFile = new File(path + downloader._tempFileNameSuffix);
                        if (tempFile.isDirectory()) break;

                        File parent = tempFile.getParentFile();
                        if (!parent.isDirectory() && !parent.mkdirs()) break;

                        finalFile = new File(path);
                        if (finalFile.isDirectory()) break;

                        long fileLen = tempFile.length();

                        host = domain.startsWith("www.") ? domain.substring(4) : domain;
                        if (fileLen > 0) {
                            if (_resumingSupport.containsKey(host) && _resumingSupport.get(host)) {
                                downloadStart = fileLen;
                            } else {
                                // Remove previous downloaded context
                                try {
                                    PrintWriter writer = new PrintWriter(tempFile);
                                    writer.print("");
                                    writer.close();
                                }
                                // Not found then nothing to do
                                catch (FileNotFoundException e) {
                                }
                            }
                        }
                    }

                    final Request.Builder builder = new Request.Builder().url(url);
                    for (int i = 0; i < header.length / 2; i++) {
                        builder.addHeader(header[i * 2], header[(i * 2) + 1]);
                    }
                    if (downloadStart > 0) {
                        builder.addHeader("RANGE", "bytes=" + downloadStart + "-");
                    }

                    final Request request = builder.build();
                    task = downloader._httpClient.newCall(request);
                    task.enqueue(new Callback() {
                        @Override
                        public void onFailure(Call call, IOException e) {
                            downloader.onFinish(id, ErrorCode.ERROR_IMPL_INTERNAL, e.toString(), null);
                        }

                        @Override
                        public void onResponse(Call call, Response response) throws IOException {
                            InputStream is = null;
                            byte[] buf = new byte[4096];
                            FileOutputStream fos = null;

                            try {
                                long total = response.body().contentLength();
                                if (path.length() > 0 && !_resumingSupport.containsKey(host)) {
                                    if (total > 0) {
                                        _resumingSupport.put(host, true);
                                    } else {
                                        _resumingSupport.put(host, false);
                                    }
                                }

                                long current = downloadStart;
                                is = response.body().byteStream();

                                if (path.length() > 0) {
                                    if (downloadStart > 0) {
                                        fos = new FileOutputStream(tempFile, true);
                                    } else {
                                        fos = new FileOutputStream(tempFile, false);
                                    }

                                    int len;
                                    while ((len = is.read(buf)) != -1) {
                                        current += len;
                                        fos.write(buf, 0, len);
                                        downloader.onProgress(id, current, len, total);
                                    }
                                    fos.flush();

                                    String errStr = null;
                                    do {
                                        // rename temp file to final file, if final file exist, remove it
                                        if (finalFile.exists()) {
                                            if (finalFile.isDirectory()) {
                                                break;
                                            }
                                            if (!finalFile.delete()) {
                                                errStr = "Can't remove old file:" + finalFile.getAbsolutePath();
                                                break;
                                            }
                                        }
                                        tempFile.renameTo(finalFile);
                                    } while (false);

                                    if (errStr == null) {
                                        downloader.onFinish(id, ErrorCode.ERROR_NO_ERROR, null, null);
                                    }
                                    else
                                        downloader.onFinish(id, ErrorCode.ERROR_IMPL_INTERNAL, errStr, null);
                                } else {
                                    // 非文件
                                    ByteArrayOutputStream buffer;
                                    if(total > 0) {
                                        buffer = new ByteArrayOutputStream((int) total);
                                    } else {
                                        buffer = new ByteArrayOutputStream(4096);
                                    }

                                    int len;
                                    while ((len = is.read(buf)) != -1) {
                                        current += len;
                                        buffer.write(buf, 0, len);
                                        downloader.onProgress(id, current, len, total);
                                    }
                                    downloader.onFinish(id, ErrorCode.ERROR_NO_ERROR, null, buffer.toByteArray());
                                }
                            } catch (IOException e) {
                                e.printStackTrace();
                                downloader.onFinish(id, ErrorCode.ERROR_FILE_OP_FAILED, e.toString(), null);
                            } finally {
                                try {
                                    if (is != null) {
                                        is.close();
                                    }
                                    if (fos != null) {
                                        fos.close();
                                    }
                                } catch (IOException e) {
                                    Log.e("Cocos2dxDownloader", e.toString());
                                }
                            }
                        }
                    });
                } while (false);

                if (null == task) {
                    final String errStr = "Can't create DownloadTask for " + url;
                    Cocos2dxHelper.runOnGLThread(new Runnable() {
                        @Override
                        public void run() {
                            downloader.nativeOnFinish(downloader._id, id, 0, errStr, null);
                        }
                    });
                } else {
                    downloader._taskMap.put(id, task);
                }
            }
        };
        downloader.enqueueTask(taskRunnable);
    }

    public static void abort(final Cocos2dxDownloader downloader, final int id) {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Call task = downloader._taskMap.remove(id);
                if(task != null) {
                    task.cancel();
                }
                downloader.runNextTaskIfExists();
            }
        });
    }

    public static void cancelAllRequests(final Cocos2dxDownloader downloader) {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                for (Call task : downloader._taskMap.values()) {
                    task.cancel();
                }
                downloader._taskMap.clear();
            }
        });
    }


    private void enqueueTask(Runnable taskRunnable) {
        synchronized (_taskQueue) {
            if (_runningTaskCount < _countOfMaxProcessingTasks) {
                Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
                _runningTaskCount++;
            } else {
                _taskQueue.add(taskRunnable);
            }
        }
    }

    private void runNextTaskIfExists() {
        synchronized (_taskQueue) {
            while (_runningTaskCount < _countOfMaxProcessingTasks && 
                Cocos2dxDownloader.this._taskQueue.size() > 0) {
                
                Runnable taskRunnable = Cocos2dxDownloader.this._taskQueue.poll();
                Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
                _runningTaskCount += 1;
            }
        }
    }

    native void nativeOnProgress(int id, int taskId, long dl, long dlnow, long dltotal);
    native void nativeOnFinish(int id, int taskId, int errCode, String errStr, final byte[] data);
}
