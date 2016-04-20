package org.cocos2dx.lib;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.AsyncHttpResponseHandler;
import com.loopj.android.http.BinaryHttpResponseHandler;
import com.loopj.android.http.FileAsyncHttpResponseHandler;
import com.loopj.android.http.RequestHandle;

import org.apache.http.Header;
import org.apache.http.message.BasicHeader;

import java.io.File;
import java.util.*;

class DataTaskHandler extends BinaryHttpResponseHandler {
    int _id;
    private Cocos2dxDownloader _downloader;
    private long _lastBytesWritten;

    void LogD(String msg) {
        android.util.Log.d("Cocos2dxDownloader", msg);
    }

    public DataTaskHandler(Cocos2dxDownloader downloader, int id) {
        super(new String[]{".*"});
        _downloader = downloader;
        _id = id;
        _lastBytesWritten = 0;
    }

    @Override
    public void onProgress(long bytesWritten, long totalSize) {
        //LogD("onProgress(bytesWritten:" + bytesWritten + " totalSize:" + totalSize);
        long dlBytes = bytesWritten - _lastBytesWritten;
        long dlNow = bytesWritten;
        long dlTotal = totalSize;
        _downloader.onProgress(_id, dlBytes, dlNow, dlTotal);
        _lastBytesWritten = bytesWritten;
    }

    @Override
    public void onStart() {
        _downloader.onStart(_id);
    }

    @Override
    public void onFailure(int i, Header[] headers, byte[] errorResponse, Throwable throwable) {
        LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable);
        String errStr = "";
        if (null != throwable) {
            errStr = throwable.toString();
        }
        _downloader.onFinish(_id, i, errStr, null);
    }

    @Override
    public void onSuccess(int i, Header[] headers, byte[] binaryData) {
        LogD("onSuccess(i:" + i + " headers:" + headers);
        _downloader.onFinish(_id, 0, null, binaryData);
    }
}

class FileTaskHandler extends FileAsyncHttpResponseHandler {
    int _id;
    File _finalFile;

    private long _initFileLen;
    private long _lastBytesWritten;
    private Cocos2dxDownloader _downloader;

    void LogD(String msg) {
        android.util.Log.d("Cocos2dxDownloader", msg);
    }

    public FileTaskHandler(Cocos2dxDownloader downloader, int id, File temp, File finalFile) {
        super(temp, true);
        _finalFile = finalFile;
        _downloader = downloader;
        _id = id;
        _initFileLen = getTargetFile().length();
        _lastBytesWritten = 0;
    }

    @Override
    public void onProgress(long bytesWritten, long totalSize) {
        //LogD("onProgress(bytesWritten:" + bytesWritten + " totalSize:" + totalSize);
        long dlBytes = bytesWritten - _lastBytesWritten;
        long dlNow = bytesWritten + _initFileLen;
        long dlTotal = totalSize + _initFileLen;
        _downloader.onProgress(_id, dlBytes, dlNow, dlTotal);
        _lastBytesWritten = bytesWritten;
    }

    @Override
    public void onStart() {
        _downloader.onStart(_id);
    }

    @Override
    public void onFinish() {
        // onFinish called after onSuccess/onFailure
        _downloader.runNextTaskIfExists();
    }

    @Override
    public void onFailure(int i, Header[] headers, Throwable throwable, File file) {
        LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable + " file:" + file);
        String errStr = "";
        if (null != throwable) {
            errStr = throwable.toString();
        }
        _downloader.onFinish(_id, i, errStr, null);
    }

    @Override
    public void onSuccess(int i, Header[] headers, File file) {
        LogD("onSuccess(i:" + i + " headers:" + headers + " file:" + file);
        String errStr = null;
        do {
            // rename temp file to final file
            // if final file exist, remove it
            if (_finalFile.exists()) {
                if (_finalFile.isDirectory()) {
                    errStr = "Dest file is directory:" + _finalFile.getAbsolutePath();
                    break;
                }
                if (false == _finalFile.delete()) {
                    errStr = "Can't remove old file:" + _finalFile.getAbsolutePath();
                    break;
                }
            }

            File tempFile = getTargetFile();
            tempFile.renameTo(_finalFile);
        } while (false);
        _downloader.onFinish(_id, 0, errStr, null);
    }
}

class DownloadTask {

    DownloadTask() {
        handle = null;
        handler = null;
        resetStatus();
    }

    void resetStatus() {
        bytesReceived = 0;
        totalBytesReceived = 0;
        totalBytesExpected = 0;
        data = null;
    }

    RequestHandle handle;
    AsyncHttpResponseHandler handler;

    // progress
    long bytesReceived;
    long totalBytesReceived;
    long totalBytesExpected;
    byte[] data;

}

public class Cocos2dxDownloader {
    private int _id;
    private AsyncHttpClient _httpClient = new AsyncHttpClient();
    private String _tempFileNameSufix;
    private int _countOfMaxProcessingTasks;
    private HashMap _taskMap = new HashMap();
    private Queue<Runnable> _taskQueue = new LinkedList<Runnable>();
    private int _runningTaskCount = 0;

    void onProgress(final int id, final long downloadBytes, final long downloadNow, final long downloadTotal) {
        DownloadTask task = (DownloadTask)_taskMap.get(id);
        if (null != task) {
            task.bytesReceived = downloadBytes;
            task.totalBytesReceived = downloadNow;
            task.totalBytesExpected = downloadTotal;
        }
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnProgress(_id, id, downloadBytes, downloadNow, downloadTotal);
            }
        });
    }

    public void onStart(int id) {
        DownloadTask task = (DownloadTask)_taskMap.get(id);
        if (null != task) {
            task.resetStatus();
        }
    }

    public void onFinish(final int id, final int errCode, final String errStr, final byte[] data) {
        DownloadTask task = (DownloadTask)_taskMap.get(id);
        if (null == task) return;
        _taskMap.remove(id);
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnFinish(_id, id, errCode, errStr, data);
            }
        });
    }

    public static Cocos2dxDownloader createDownloader(int id, int timeoutInSeconds, String tempFileNameSufix, int countOfMaxProcessingTasks) {
        Cocos2dxDownloader downloader = new Cocos2dxDownloader();
        downloader._id = id;

        downloader._httpClient.setEnableRedirects(true);
        if (timeoutInSeconds > 0) {
            downloader._httpClient.setTimeout(timeoutInSeconds * 1000);
        }
        // downloader._httpClient.setMaxRetriesAndTimeout(3, timeoutInSeconds * 1000);
        downloader._httpClient.allowRetryExceptionClass(javax.net.ssl.SSLException.class);

        downloader._tempFileNameSufix = tempFileNameSufix;
        downloader._countOfMaxProcessingTasks = countOfMaxProcessingTasks;
        return downloader;
    }

    public static void createTask(final Cocos2dxDownloader downloader, int id_, String url_, String path_) {
        final int id = id_;
        final String url = url_;
        final String path = path_;

        Runnable taskRunnable = new Runnable() {
            @Override
            public void run() {
                DownloadTask task = new DownloadTask();
                if (0 == path.length()) {
                    // data task
                    task.handler = new DataTaskHandler(downloader, id);
                    task.handle = downloader._httpClient.get(Cocos2dxHelper.getActivity(), url, task.handler);
                }

                do {
                    if (0 == path.length()) break;
                    // file task
                    File tempFile = new File(path + downloader._tempFileNameSufix);
                    if (tempFile.isDirectory()) break;

                    File parent = tempFile.getParentFile();
                    if (!parent.isDirectory() && !parent.mkdirs()) break;

                    File finalFile = new File(path);
                    if (tempFile.isDirectory()) break;

                    task.handler = new FileTaskHandler(downloader, id, tempFile, finalFile);
                    Header[] headers = null;
                    long fileLen = tempFile.length();
                    if (fileLen > 0) {
                        // continue download
                        List<Header> list = new ArrayList<Header>();
                        list.add(new BasicHeader("Range", "bytes=" + fileLen + "-"));
                        headers = list.toArray(new Header[list.size()]);
                    }
                    task.handle = downloader._httpClient.get(Cocos2dxHelper.getActivity(), url, headers, null, task.handler);
                    //task.handle = downloader._httpClient.get(url, task.handler);
                } while (false);

                if (null == task.handle) {
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

    public static void cancelAllRequests(final Cocos2dxDownloader downloader) {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {

                //downloader._httpClient.cancelAllRequests(true);
                Iterator iter = downloader._taskMap.entrySet().iterator();
                while (iter.hasNext()) {
                    Map.Entry entry = (Map.Entry) iter.next();
                    //Object key = entry.getKey();
                    DownloadTask task = (DownloadTask) entry.getValue();
                    if (null != task.handle) {
                        task.handle.cancel(true);
                    }
                }
            }
        });
    }


    public void enqueueTask(Runnable taskRunnable) {
        synchronized (_taskQueue) {
            if (_runningTaskCount < _countOfMaxProcessingTasks) {
                Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
                _runningTaskCount++;
            } else {
                _taskQueue.add(taskRunnable);
            }
        }
    }

    public void runNextTaskIfExists() {
        synchronized (_taskQueue) {
            Runnable taskRunnable = Cocos2dxDownloader.this._taskQueue.poll();
            if (taskRunnable != null) {
                Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
            } else {
                _runningTaskCount--;
            }
        }
    }

    native void nativeOnProgress(int id, int taskId, long dl, long dlnow, long dltotal);
    native void nativeOnFinish(int id, int taskId, int errCode, String errStr, final byte[] data);
}
