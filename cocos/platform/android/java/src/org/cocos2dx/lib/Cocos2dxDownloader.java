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

import android.util.SparseArray;

class DataTaskHandler extends BinaryHttpResponseHandler {
    int mId;
    private Cocos2dxDownloader mDownloader;
    private long mLastBytesWritten;

    void LogD(String msg) {
        android.util.Log.d("Cocos2dxDownloader", msg);
    }

    public DataTaskHandler(Cocos2dxDownloader downloader, int id) {
        super(new String[]{".*"});
        mDownloader = downloader;
        mId = id;
        mLastBytesWritten = 0;
    }

    @Override
    public void onProgress(long bytesWritten, long totalSize) {
        //LogD("onProgress(bytesWritten:" + bytesWritten + " totalSize:" + totalSize);
        long dlBytes = bytesWritten - mLastBytesWritten;
        long dlNow = bytesWritten;
        long dlTotal = totalSize;
        mDownloader.onProgress(mId, dlBytes, dlNow, dlTotal);
        mLastBytesWritten = bytesWritten;
    }

    @Override
    public void onStart() {
        mDownloader.onStart(mId);
    }

    @Override
    public void onFailure(int i, Header[] headers, byte[] errorResponse, Throwable throwable) {
        LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable);
        String errStr = "";
        if (null != throwable) {
            errStr = throwable.toString();
        }
        mDownloader.onFinish(mId, i, errStr, null);
    }

    @Override
    public void onSuccess(int i, Header[] headers, byte[] binaryData) {
        LogD("onSuccess(i:" + i + " headers:" + headers);
        mDownloader.onFinish(mId, 0, null, binaryData);
    }
}

class FileTaskHandler extends FileAsyncHttpResponseHandler {
    int mId;
    File mFinalFile;

    private long mInitFileLen;
    private long mLastBytesWritten;
    private Cocos2dxDownloader mDownloader;

    void LogD(String msg) {
        android.util.Log.d("Cocos2dxDownloader", msg);
    }

    public FileTaskHandler(Cocos2dxDownloader downloader, int id, File temp, File finalFile) {
        super(temp, true);
        mFinalFile = finalFile;
        mDownloader = downloader;
        mId = id;
        mInitFileLen = getTargetFile().length();
        mLastBytesWritten = 0;
    }

    @Override
    public void onProgress(long bytesWritten, long totalSize) {
        //LogD("onProgress(bytesWritten:" + bytesWritten + " totalSize:" + totalSize);
        long dlBytes = bytesWritten - mLastBytesWritten;
        long dlNow = bytesWritten + mInitFileLen;
        long dlTotal = totalSize + mInitFileLen;
        mDownloader.onProgress(mId, dlBytes, dlNow, dlTotal);
        mLastBytesWritten = bytesWritten;
    }

    @Override
    public void onStart() {
        mDownloader.onStart(mId);
    }

    @Override
    public void onFinish() {
        // onFinish called after onSuccess/onFailure
        mDownloader.runNextTaskIfExists();
    }

    @Override
    public void onFailure(int i, Header[] headers, Throwable throwable, File file) {
        LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable + " file:" + file);
        String errStr = "";
        if (null != throwable) {
            errStr = throwable.toString();
        }
        mDownloader.onFinish(mId, i, errStr, null);
    }

    @Override
    public void onSuccess(int i, Header[] headers, File file) {
        LogD("onSuccess(i:" + i + " headers:" + headers + " file:" + file);
        String errStr = null;
        do {
            // rename temp file to final file
            // if final file exist, remove it
            if (mFinalFile.exists()) {
                if (mFinalFile.isDirectory()) {
                    errStr = "Dest file is directory:" + mFinalFile.getAbsolutePath();
                    break;
                }
                if (false == mFinalFile.delete()) {
                    errStr = "Can't remove old file:" + mFinalFile.getAbsolutePath();
                    break;
                }
            }

            File tempFile = getTargetFile();
            tempFile.renameTo(mFinalFile);
        } while (false);
        mDownloader.onFinish(mId, 0, errStr, null);
    }
}

class DownloadTask {

    DownloadTask(int id, String url, String path) {
        mHandle = null;
        mHandler = null;
        mId = id;
        mUrl = url;
        mPath = path;
        resetStatus();
    }

    void resetStatus() {
        mBytesReceived = 0;
        mTotalBytesReceived = 0;
        mTotalBytesExpected = 0;
    }
    
    boolean isDataTask() {
        return mPath.isEmpty();
    }

    RequestHandle mHandle;
    AsyncHttpResponseHandler mHandler;

    // progress
    long mBytesReceived;
    long mTotalBytesReceived;
    long mTotalBytesExpected;
    
    // task info for resuming
    int mId;
    String mUrl;
    String mPath;
}

public class Cocos2dxDownloader {
    private int mId;
    private AsyncHttpClient mHttpClient = new AsyncHttpClient();
    private String mTempFileNameSufix;
    private int mCountOfMaxProcessingTasks;
    private SparseArray<DownloadTask> mRunningTasks = new SparseArray<DownloadTask>();
    private Queue<Runnable> mTaskCreationQueue = new LinkedList<Runnable>();
    private boolean mIsSuspended = false;

    void onProgress(final int id, final long downloadBytes, final long downloadNow, final long downloadTotal) {
        DownloadTask task = (DownloadTask)mRunningTasks.get(id);
        if (null != task) {
            task.mBytesReceived = downloadBytes;
            task.mTotalBytesReceived = downloadNow;
            task.mTotalBytesExpected = downloadTotal;
        }
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnProgress(mId, id, downloadBytes, downloadNow, downloadTotal);
            }
        });
    }

    public void onStart(int id) {
        DownloadTask task = (DownloadTask)mRunningTasks.get(id);
        if (null != task) {
            task.resetStatus();
        }
    }

    public void onFinish(final int id, final int errCode, final String errStr, final byte[] data) {
        DownloadTask task = (DownloadTask)mRunningTasks.get(id);
        if (null == task) return;
        mRunningTasks.remove(id);
        Cocos2dxHelper.runOnGLThread(new Runnable() {
            @Override
            public void run() {
                nativeOnFinish(mId, id, errCode, errStr, data);
            }
        });
    }

    // BEGIN: static methods for calling from JNI
    
    public static Cocos2dxDownloader createDownloader(int id, int timeoutInSeconds, String tempFileNameSufix, int countOfMaxProcessingTasks) {
        Cocos2dxDownloader downloader = new Cocos2dxDownloader();
        downloader.mId = id;

        downloader.mHttpClient.setEnableRedirects(true);
        if (timeoutInSeconds > 0) {
            downloader.mHttpClient.setTimeout(timeoutInSeconds * 1000);
        }
        // downloader.mHttpClient.setMaxRetriesAndTimeout(3, timeoutInSeconds * 1000);
        AsyncHttpClient.allowRetryExceptionClass(javax.net.ssl.SSLException.class);

        downloader.mTempFileNameSufix = tempFileNameSufix;
        downloader.mCountOfMaxProcessingTasks = countOfMaxProcessingTasks;
        return downloader;
    }
    
    public static void createTask(final Cocos2dxDownloader downloader, final int id, final String url, final String path) {
        Runnable createTaskRunnable = new Runnable() {
            @Override
            public void run() {
                downloader.createTask(id, url, path);
            }
        };
        downloader.enqueueTask(createTaskRunnable);
    }

    public static void cancelAllRequests(final Cocos2dxDownloader downloader) {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                downloader.cancelAllRequests();
            }
        });
    }
 // END: static methods for calling from JNI
    
    public boolean isSuspended() {
        return mIsSuspended;
    }
    
    private void startDataTask(DownloadTask task) {
        task.mHandler = new DataTaskHandler(this, task.mId);
        // do not start the request if downloader is currently suspended
        if (!mIsSuspended) {
            task.mHandle = mHttpClient.get(Cocos2dxHelper.getActivity(), task.mUrl, task.mHandler);
        }
    }
    
    private void startFileTask(DownloadTask task) throws IllegalArgumentException {
        File tempFile = new File(task.mPath + mTempFileNameSufix);
        if (tempFile.isDirectory()) throw new IllegalArgumentException();

        File parent = tempFile.getParentFile();
        if (!parent.isDirectory() && !parent.mkdirs()) throw new IllegalArgumentException();

        File finalFile = new File(task.mPath);
        if (finalFile.isDirectory()) throw new IllegalArgumentException();

        task.mHandler = new FileTaskHandler(this, task.mId, tempFile, finalFile);
        
        // do not start the request if downloader is currently suspended
        if (!mIsSuspended) {
            Header[] headers = null;
            long fileLen = tempFile.length();
            if (fileLen > 0) {
                // continue download
                List<Header> list = new ArrayList<Header>();
                list.add(new BasicHeader("Range", "bytes=" + fileLen + "-"));
                headers = list.toArray(new Header[list.size()]);
            }
            task.mHandle = mHttpClient.get(Cocos2dxHelper.getActivity(), task.mUrl, headers, null, task.mHandler);
        }
    }
    
    private void createTask(final int id, final String url, final String path) {
        DownloadTask task = new DownloadTask(id, url, path);
        try {
            if (task.isDataTask()) {
                startDataTask(task);
            } else {
                startFileTask(task);
            }
        } catch (IllegalArgumentException e) {
            final String errStr = "Can't create DownloadTask for " + url;
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    nativeOnFinish(mId, id, 0, errStr, null);
                }
            });
            return;
        }
        mRunningTasks.put(id, task);
    }
    
    public void cancelAllRequests() {
        for (int i = 0; i < mRunningTasks.size(); i++) {
            DownloadTask task = mRunningTasks.valueAt(i);
            if (null != task.mHandle) {
                task.mHandle.cancel(true);
            }
        }
    }

    public void suspend() {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                synchronized (mTaskCreationQueue) {
                    mIsSuspended = true;
                    for (int i = 0; i < mRunningTasks.size(); i++) {
                        DownloadTask task = mRunningTasks.valueAt(i);
                        if (null != task.mHandle) {
                            task.mHandle.cancel(true);
                        }
                    }
                }
            }
        });
    }

    public void resume() {
        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                synchronized (mTaskCreationQueue) {
                    mIsSuspended = false;
                    for (int i = 0; i < mRunningTasks.size(); i++) {
                        DownloadTask task = mRunningTasks.valueAt(i);
                        if (task.mHandle == null || task.mHandle.isCancelled()) {
                            task.resetStatus();
                            if (task.isDataTask()) {
                                startDataTask(task);
                            } else {
                                startFileTask(task);
                            }
                        }
                    }
                }
            }
        });
    }

    private void enqueueTask(Runnable taskRunnable) {
        synchronized (mTaskCreationQueue) {
            if (mRunningTasks.size() < mCountOfMaxProcessingTasks) {
                Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
            } else {
                mTaskCreationQueue.add(taskRunnable);
            }
        }
    }

    public void runNextTaskIfExists() {
        synchronized (mTaskCreationQueue) {
            Runnable createTaskRunnable = Cocos2dxDownloader.this.mTaskCreationQueue.poll();
            if (createTaskRunnable != null) {
                Cocos2dxHelper.getActivity().runOnUiThread(createTaskRunnable);
            }
        }
    }

    native void nativeOnProgress(int id, int taskId, long dl, long dlnow, long dltotal);
    native void nativeOnFinish(int id, int taskId, int errCode, String errStr, final byte[] data);
}
