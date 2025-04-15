export class Result {
    public static success(data){
        return {
            "errCode": 0,
            "errMsg": "",
            "data": data,
        };
    }

    public static error(errCode, errMsg) {
        return {
            "errCode": errCode,
            "errMsg": errMsg,
        };
    }
};