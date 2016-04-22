package org.cocos2dx.lib;

import java.io.File;
import java.util.LinkedList;
import java.util.Queue;

import org.apache.http.Header;
import org.apache.http.message.BasicHeader;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.BinaryHttpResponseHandler;
import com.loopj.android.http.FileAsyncHttpResponseHandler;
import com.loopj.android.http.RequestHandle;

import android.util.SparseArray;

public class Cocos2dxDownloader {
    private int _id;
    private AsyncHttpClient _httpClient;
    private String _tempFileNameSufix;
    private int _countOfMaxProcessingTasks;
    
    private int runningTasks;
    private Queue<Runnable> _taskQueue;

    private SparseArray<RequestHandle> taskHandles;

    static {
	AsyncHttpClient.allowRetryExceptionClass(javax.net.ssl.SSLException.class);
    }

    @Deprecated
    public Cocos2dxDownloader() {
    }
    public Cocos2dxDownloader(int id, int timeoutInSeconds, String tempFileNameSufix, int countOfMaxProcessingTasks) {
	_id = id;

	_httpClient = new AsyncHttpClient();
	_httpClient.setEnableRedirects(true);
	if (timeoutInSeconds > 0) {
	    _httpClient.setTimeout(timeoutInSeconds * 1000);
	}

	_tempFileNameSufix = tempFileNameSufix;
	_countOfMaxProcessingTasks = countOfMaxProcessingTasks;

	_taskQueue = new LinkedList<Runnable>();

	taskHandles = new SparseArray<RequestHandle>();
    }

    public void onStart(int id) {
    }

    void onProgress(final int taskID, final long downloadBytes, final long downloadNow, final long downloadTotal) {
	Cocos2dxHelper.runOnGLThread(new Runnable() {
	    @Override
	    public void run() {
		nativeOnProgress(_id, taskID, downloadBytes, downloadNow, downloadTotal);
	    }
	});
    }

    public void onFinish(final int taskID, final int errCode, final String errStr, final byte[] data) {
	RequestHandle handle = taskHandles.get(taskID);
	if (handle != null) {
	    taskHandles.remove(taskID);
	}
	Cocos2dxHelper.runOnGLThread(new Runnable() {
	    @Override
	    public void run() {
		nativeOnFinish(_id, taskID, errCode, errStr, data);
	    }
	});
	
	synchronized (_taskQueue) {
	    Runnable taskRunnable = Cocos2dxDownloader.this._taskQueue.poll();
	    if (taskRunnable != null) {
		Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
	    } else {
		runningTasks--;
	    }
	}
    }

    @Deprecated
    public static Cocos2dxDownloader createDownloader(int id, int timeoutInSeconds, String tempFileNameSufix, int countOfMaxProcessingTasks) {
	return new Cocos2dxDownloader(id, timeoutInSeconds, tempFileNameSufix, countOfMaxProcessingTasks);
    }

    public void createTask(final int taskID, final String url, final String path) {
	Runnable taskRunnable = new Runnable() {
	    @Override
	    public void run() {
		RequestHandle handle;

		if (0 == path.length()) {
		    // data task
		    DataTaskHandler handler = new DataTaskHandler(taskID);
		    handle = _httpClient.get(Cocos2dxHelper.getActivity(), url, handler);
		} else {
		    // file task
		    File tempFile = new File(path + _tempFileNameSufix);
		    if (tempFile.isDirectory()) {
			final String errStr = "Can't create DownloadTask for " + url + ". Unable to create temp file: " + tempFile;
			Cocos2dxHelper.runOnGLThread(new Runnable() {
			    @Override
			    public void run() {
				nativeOnFinish(_id, taskID, 0, errStr, null);
			    }
			});
			return;
		    }

		    File parent = tempFile.getParentFile();
		    if (!parent.isDirectory() && !parent.mkdirs()) {
			final String errStr = "Can't create DownloadTask for " + url + ". Unable to create temp file directory: " + parent;
			Cocos2dxHelper.runOnGLThread(new Runnable() {
			    @Override
			    public void run() {
				nativeOnFinish(_id, taskID, 0, errStr, null);
			    }
			});
			return;
		    }

		    File finalFile = new File(path);
		    if (finalFile.isDirectory()) {
			final String errStr = "Can't create DownloadTask for " + url + ". Unable to create file: " + finalFile;
			Cocos2dxHelper.runOnGLThread(new Runnable() {
			    @Override
			    public void run() {
				nativeOnFinish(_id, taskID, 0, errStr, null);
			    }
			});
			return;
		    }

		    FileTaskHandler handler = new FileTaskHandler(taskID, tempFile, finalFile);
		    Header[] headers = null;
		    long fileLen = tempFile.length();
		    if (fileLen > 0) {
			// continue download
			headers = new Header[1];
			headers[0] = new BasicHeader("Range", "bytes=" + fileLen + "-");
		    }
		    handle = _httpClient.get(Cocos2dxHelper.getActivity(), url, headers, null, handler);
		    //task.handle = downloader._httpClient.get(url, task.handler);
		}

		taskHandles.put(taskID, handle);
	    }
	};
	
	synchronized (_taskQueue) {
	    if (runningTasks < _countOfMaxProcessingTasks) {
		Cocos2dxHelper.getActivity().runOnUiThread(taskRunnable);
		runningTasks++;
	    } else {
		_taskQueue.add(taskRunnable);
	    }
	}
    }
    @Deprecated
    public static void createTask(final Cocos2dxDownloader downloader, final int taskID, final String url, final String path) {
	downloader.createTask(taskID, url, path);
    }

    public void cancelAllRequests() {
	Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
	    @Override
	    public void run() {
		int s = taskHandles.size();
		for (int i = 0; i < s; i++) {
		    RequestHandle handle = taskHandles.valueAt(i);
		    if (handle != null) {
			handle.cancel(true);
		    }
		}
	    }
	});
    }
    @Deprecated
    public static void cancelAllRequests(final Cocos2dxDownloader downloader) {
	downloader.cancelAllRequests();
    }

    native void nativeOnProgress(int id, int taskId, long dl, long dlnow, long dltotal);
    native void nativeOnFinish(int id, int taskId, int errCode, String errStr, final byte[] data);

    private class DataTaskHandler extends BinaryHttpResponseHandler {
	int _id;
	private long _lastBytesWritten;

	void LogD(String msg) {
	    android.util.Log.d("Cocos2dxDownloader", msg);
	}

	public DataTaskHandler(int id) {
	    super(new String[]{".*"});
	    _id = id;
	    _lastBytesWritten = 0;
	}

	@Override
	public void onProgress(long bytesWritten, long totalSize) {
	    //LogD("onProgress(bytesWritten:" + bytesWritten + " totalSize:" + totalSize);
	    long dlBytes = bytesWritten - _lastBytesWritten;
	    long dlNow = bytesWritten;
	    long dlTotal = totalSize;
	    Cocos2dxDownloader.this.onProgress(_id, dlBytes, dlNow, dlTotal);
	    _lastBytesWritten = bytesWritten;
	}

	@Override
	public void onStart() {
	    Cocos2dxDownloader.this.onStart(_id);
	}

	@Override
	public void onFailure(int i, Header[] headers, byte[] errorResponse, Throwable throwable) {
	    LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable);
	    String errStr = null;
	    if (null != throwable) {
		errStr = throwable.toString();
	    }
	    Cocos2dxDownloader.this.onFinish(_id, i, errStr, null);
	}

	@Override
	public void onSuccess(int i, Header[] headers, byte[] binaryData) {
	    LogD("onSuccess(i:" + i + " headers:" + headers);
	    Cocos2dxDownloader.this.onFinish(_id, 0, null, binaryData);
	}
    }

    private class FileTaskHandler extends FileAsyncHttpResponseHandler {
	int _id;
	File _finalFile;

	private long _initFileLen;
	private long _lastBytesWritten;

	void LogD(String msg) {
	    android.util.Log.d("Cocos2dxDownloader", msg);
	}

	public FileTaskHandler(int id, File temp, File finalFile) {
	    super(temp, true);
	    _finalFile = finalFile;
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
	    Cocos2dxDownloader.this.onProgress(_id, dlBytes, dlNow, dlTotal);
	    _lastBytesWritten = bytesWritten;
	}

	@Override
	public void onStart() {
	    Cocos2dxDownloader.this.onStart(_id);
	}

	@Override
	public void onFailure(int i, Header[] headers, Throwable throwable, File file) {
	    LogD("onFailure(i:" + i + " headers:" + headers + " throwable:" + throwable + " file:" + file);
	    String errStr = "";
	    if (null != throwable) {
		errStr = throwable.toString();
	    }
	    Cocos2dxDownloader.this.onFinish(_id, i, errStr, null);
	}

	@Override
	public void onSuccess(int i, Header[] headers, File file) {
	    LogD("onSuccess(i:" + i + " headers:" + headers + " file:" + file);
	    String errStr = null;

	    // rename temp file to final file
	    // if final file exist, remove it
	    if (_finalFile.exists()) {
		if (_finalFile.isDirectory()) {
		    errStr = "Dest file is directory:" + _finalFile.getAbsolutePath();
		    Cocos2dxDownloader.this.onFinish(_id, 0, errStr, null);
		    return;
		}
		if (false == _finalFile.delete()) {
		    errStr = "Can't remove old file:" + _finalFile.getAbsolutePath();
		    Cocos2dxDownloader.this.onFinish(_id, 0, errStr, null);
		    return;
		}
	    }

	    File tempFile = getTargetFile();
	    tempFile.renameTo(_finalFile);
	    Cocos2dxDownloader.this.onFinish(_id, 0, errStr, null);
	}
    }
}
