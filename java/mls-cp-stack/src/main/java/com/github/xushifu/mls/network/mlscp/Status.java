package com.github.xushifu.mls.network.mlscp;

import com.github.xushifu.mls.utils.Strings;

public final class Status {

    private int code;
    private String message;

    public Status() {
        this.code = 0;
        this.message = "";
    }

    public Status(int _code, String _msg) {
        this.code = _code;
        this.message = Strings.useEmpty(_msg);
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    @Override
    public String toString() {
        return code + ": " + message;
    }

}
