package org.cocos2dx.lib;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.ProtocolException;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Map.Entry;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

public class QuickHTTPInterface {
    static String BOUNDARY = "----------------------------78631b43218d";
    static String NEWLINE = "\r\n";

    static HttpURLConnection createURLConnect(String strURL) {
        URL url;
        HttpURLConnection urlConnection;
        try {
            url = new URL(strURL);
            urlConnection = (HttpURLConnection)url.openConnection();
            urlConnection.setRequestProperty("Accept-Encoding", "identity");
            urlConnection.setDoInput(true);
        } catch (Exception e) {
            Log.e("QuickHTTPInterface", e.toString());
            return null;
        }

        return urlConnection;
    }

    static void setRequestMethod(HttpURLConnection http, String strMedthod) {
        try {
            if ("POST".equalsIgnoreCase(strMedthod)) {
                http.setDoOutput(true);
                http.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            }
            http.setRequestMethod(strMedthod);
        } catch (ProtocolException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void addRequestHeader(HttpURLConnection http, String strkey, String strValue, boolean bNeedBoundary) {
        if ("Content-Type".equalsIgnoreCase(strkey.trim()) && bNeedBoundary) {
            strValue += ("; boundary=" + BOUNDARY);
        }
        http.setRequestProperty(strkey, strValue);
    }

    static void setTimeout(HttpURLConnection http, int msTime) {
        http.setConnectTimeout(msTime);
        http.setReadTimeout(msTime);
    }

    static int connect(HttpURLConnection http) {
        int nSuc = 0;

        try {
            http.connect();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
            nSuc = 1;
        }

        return nSuc;
    }

    static void postContent(HttpURLConnection http, String name, String value, boolean bNeedConnectSym) {
        try {
            DataOutputStream out = new DataOutputStream(http.getOutputStream());
            String content = null;
            if (null == name || 0 == name.length()) {
                content = java.net.URLEncoder.encode(value, "utf-8");
            } else {
                content = java.net.URLEncoder.encode(name, "utf-8") + "=" + java.net.URLEncoder.encode(value, "utf-8");
            }
            if (bNeedConnectSym) {
                content = "&" + content;
            }

            out.write(content.getBytes());
            out.flush();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void postContentByteArray(HttpURLConnection http, byte[] byteArray) {
        try {
            OutputStream out = http.getOutputStream();

            out.write(byteArray);

            out.flush();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void postFormContent(HttpURLConnection http, String key, String val) {
        try {
            OutputStream out = http.getOutputStream();

            out.write(getBoundaryContentHeader(key, val).getBytes());

            out.flush();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void postFormFile(HttpURLConnection http, String name, String filePath) {
        try {
            FileInputStream fin = new FileInputStream(filePath);
            OutputStream out = http.getOutputStream();


            out.write(getBoundaryFileHeader(name, filePath).getBytes());
            byte[] buffer = new byte[1024];
            int len = 0;
            while((len = fin.read(buffer)) != -1) {
                out.write(buffer, 0, len);
            }
            out.write(NEWLINE.getBytes());

            out.flush();
            fin.close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static void postFormEnd(HttpURLConnection http, boolean bBoundary) {
        if ("GET".equalsIgnoreCase(http.getRequestMethod())) {
            return;
        }

        try {
            OutputStream out = http.getOutputStream();

            if (bBoundary) {
                out.write(getBoundaryEnd().getBytes());
                out.flush();
            }
            out.close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
    }

    static String getBoundaryFileHeader(String key, String filePath) {
        File file = new File(filePath);
        StringBuilder sb = new StringBuilder();
        sb.append("--");
        sb.append(BOUNDARY);
        sb.append(NEWLINE);
        sb.append("Content-Disposition: form-data; ");
        sb.append("name=\"");
        sb.append(key);
        sb.append("\"; ");
        sb.append("filename=\"");
        sb.append(file.getName());
        sb.append("\"");
        sb.append(NEWLINE);
        sb.append("Content-Type: application/octet-stream");
        sb.append(NEWLINE);
        sb.append(NEWLINE);

        return sb.toString();
    }

    static String getBoundaryContentHeader(String key, String val) {
        StringBuilder sb = new StringBuilder();
        sb.append("--");
        sb.append(BOUNDARY);
        sb.append(NEWLINE);
        sb.append("Content-Disposition: form-data; name=\"");
        sb.append(key);
        sb.append("\"");
        sb.append(NEWLINE);
        sb.append(NEWLINE);
        sb.append(val);
        sb.append(NEWLINE);

        return sb.toString();
    }

    static String getBoundaryEnd() {
        StringBuilder sb = new StringBuilder();
        sb.append("--");
        sb.append(BOUNDARY);
        sb.append("--");
        sb.append(NEWLINE);

        return sb.toString();
    }

    static int getResponedCode(HttpURLConnection http) {
        int code = 0;
        try {
            code = http.getResponseCode();
            //            Log.i("QuickHTTPInterface", "reponed code:" + code);
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
        return code;
    }

    static String getResponedErr(HttpURLConnection http) {
        String msg;
        try {
            msg = http.getResponseMessage();
        } catch (IOException e) {
            msg = e.toString();
            Log.e("QuickHTTPInterface", msg);
        }

        return msg;
    }

    static String getResponedHeader(HttpURLConnection http) {
        Map<String, List<String>> headers = http.getHeaderFields();

        JSONObject json = new JSONObject();
        try {
            for (Entry<String, List<String>> entry: headers.entrySet()) {
                String key = entry.getKey();
                if (null == key) {
                    key = "";
                }
                List<String> value = entry.getValue();
                JSONArray jsonArray = new JSONArray();
                for(String strVal : value) {
                    jsonArray.put(strVal);
                }
                json.put(key, jsonArray);
            }
        } catch(JSONException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }

        return json.toString();
    }

    static String getResponedHeaderByIdx(HttpURLConnection http, int idx) {
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

    static String getResponedHeaderByKey(HttpURLConnection http, String key) {
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

    static int getResponedHeaderByKeyInt(HttpURLConnection http, String key) {
        String value = http.getHeaderField(key);

        if (null == value) {
            return 0;
        } else {
            return Integer.parseInt(value);
        }
    }

    static int getContentLeng(HttpURLConnection http) {
        return http.getContentLength();
    }

    static byte[] getResponedString(HttpURLConnection http) {
        try {
            DataInputStream in = new DataInputStream(http.getInputStream());

            byte[] buffer = new byte[1024];
            byte[] retBuf = null;
            int len = in.read(buffer);
            //            Log.i("QuickHTTPInterface", "have recv data:" + len);

            if (-1 == len) {
                retBuf = new byte[1];
                retBuf[0] = 0;
            } else {
                retBuf = new byte[len+1];
                retBuf[0] = 1;
                System.arraycopy(buffer, 0, retBuf, 1, len);
            }
            return retBuf;
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }

        return null;
    }

    static void close(HttpURLConnection http) {
        try {
            http.getInputStream().close();
        } catch (IOException e) {
            Log.e("QuickHTTPInterface", e.toString());
        }
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

    public static String combinCookies(List<String> list, String strDomain) {
        StringBuilder sbCookies = new StringBuilder();

        String strKey = null;
        String strValue = null;
        String strExpire = null;
        boolean bSecure = false;
        boolean bFirst = false;

        for (String str : list) {
        	bSecure = false;
        	bFirst = true;
            String[] parts = str.split(";");
            for (String part : parts) {
                String[] item = part.split("=");
                if (bFirst) {
                	if (2 == item.length) {
                		strKey = item[0];
                		strValue = item[1];
                	} else {
                		strKey = "";
                		strValue = "";
                	}
                	bFirst = false;
                }
                if ("expires".equalsIgnoreCase(item[0].trim())) {
                    strExpire = str2Seconds(item[1].trim());
                } else if("secure".equalsIgnoreCase(item[0].trim())) {
                	bSecure = true;
                } else if ("domain".equalsIgnoreCase(item[0].trim())) {
                	strDomain = item[1];
                }
            }

            if (null == strDomain) {
                strDomain = "none";
            }

            sbCookies.append(strDomain);
            sbCookies.append('\t');
            sbCookies.append("FALSE\t");       //access
            sbCookies.append("/\t");          //path
            if (bSecure) {
            	sbCookies.append("TRUE\t");     //secure
            } else {
            	sbCookies.append("FALSE\t");     //secure
            }
            sbCookies.append(strExpire);    //expire tag
            sbCookies.append("\t");
            sbCookies.append(strKey);       //key
            sbCookies.append("\t");
            sbCookies.append(strValue);     //value
            sbCookies.append('\n');
        }

        return sbCookies.toString();
    }

    private static String str2Seconds(String strTime) {
        Calendar c = Calendar.getInstance();
        long millisSecond = 0;

        try {
            c.setTime(new SimpleDateFormat("EEE, dd-MMM-yyyy hh:mm:ss zzz", Locale.US).parse(strTime));
            millisSecond = c.getTimeInMillis()/1000;
        } catch (ParseException e) {
        	millisSecond = -1;
            //Log.e("QuickHTTPInterface", e.toString());
        }
        
        if (-1 == millisSecond) {
        	return strTime;
        }

        return Long.toString(millisSecond);
    }

}
