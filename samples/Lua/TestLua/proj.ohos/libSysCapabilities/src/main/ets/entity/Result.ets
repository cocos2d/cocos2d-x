interface ResultObjectInterface {
    "errCode": number;
    "errMsg": string;
    "data": string,
}

export class Result {
    public static success(data: string){
        return ({
            "errCode": 0,
            "errMsg": "",
            "data": data,
        }as ResultObjectInterface);
    }

    public static error(errCode:number, errMsg:string){
        return ({
            "errCode": errCode,
            "errMsg": errMsg,
            "data": "",
        } as ResultObjectInterface);
    }
};