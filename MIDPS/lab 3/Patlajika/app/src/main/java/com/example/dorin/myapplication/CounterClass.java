package com.example.dorin.myapplication;

import android.os.CountDownTimer;

import java.util.concurrent.TimeUnit;


public class CounterClass extends CountDownTimer {

    Laborator3 laborator3;
    long elapsed;

    public CounterClass(long milisInFuture, long countDownInterval, Laborator3 laborator3) {
        super(milisInFuture, countDownInterval);
        this.laborator3 = laborator3;
        elapsed = milisInFuture;

    }

    @Override
    public void onTick(long millisUntilFinished) {
        long millis = millisUntilFinished;
        String hms = String.format("%02d:%02d:%02d", TimeUnit.MILLISECONDS.toHours(millis),
                TimeUnit.MILLISECONDS.toMinutes(millis) - TimeUnit.HOURS.toMinutes(TimeUnit.MILLISECONDS.toHours(millis)),
                TimeUnit.MILLISECONDS.toSeconds(millis) - TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(millis)));
        System.out.println(hms);
        laborator3.setTime(hms);
        laborator3.setProgressMethod((int)(millisUntilFinished/(double)elapsed * 100));
    }

    @Override
    public void onFinish() {
        laborator3.setTime("Completed.");
    }

}