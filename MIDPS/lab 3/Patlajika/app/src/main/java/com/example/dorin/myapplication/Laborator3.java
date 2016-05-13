package com.example.dorin.myapplication;


import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;
import com.example.dorin.myapplication.CounterClass;


import java.util.concurrent.TimeUnit;

public class Laborator3 extends AppCompatActivity {

    Button btnStart, btnStop;
    TextView textViewTime;
    EditText editText;
    SeekBar seekBar;
    CounterClass timer;
    Laborator3 activity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_laborator3);
        activity = this;
        btnStart = (Button) findViewById(R.id.btnStart);
        btnStop = (Button) findViewById(R.id.btnStop);
        textViewTime = (TextView) findViewById(R.id.textViewTime);
        editText = (EditText) findViewById(R.id.editText);
        seekBar = (SeekBar) findViewById(R.id.seekBar);
        seekBar.setActivated(false);
        seekBar.setProgress(100);
        textViewTime.setText("Elapsed time");


        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                timer = new CounterClass(Long.parseLong(String.valueOf(editText.getText())), 1000, activity);
                timer.start();
                Log.e("ewqewqe" , editText.getText().toString());
            }
        });
        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                timer.cancel();
            }
        });

    }

    public void setTime(String time) {
        textViewTime.setText(time);
    }

    public void setProgressMethod(int progress) {
        seekBar.setProgress(progress);
    }


}
