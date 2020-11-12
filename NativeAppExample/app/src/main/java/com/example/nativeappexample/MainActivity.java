package com.example.nativeappexample;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements JNICallBackInterface{


    private NativeLibrary nativeLibrary;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        nativeLibrary = new NativeLibrary(this);
        // Example of a call to a native method
    }

    /**
     * On Get String From JNI Button Clicked Event
     *
     * @param view
     */
    public void onGetStringFromJNIButtonClicked(View view){
        // Define text view to update
        TextView textView = findViewById(R.id.textViewGetStringFromJNI);

        // Get String From JNI
        String stringFromJNI = nativeLibrary.stringFromJNI();

        // Update Text Box
        textView.setText(stringFromJNI);

    }

    /**
     * On Pass Data To JNI Button Clicked Event
     *
     * @param view
     */
    public void onPassDataToJNIButtonClicked(View view){
        TextView textView = findViewById(R.id.textViewPassDataToJNI);

        // Temp data which passing to JNI
        double[] tmpArray = {1, 2, 3};
        int tmpInt = 1;
        float tmpFloat = 2.3f;

        int returnValue = nativeLibrary.passingDataToJni(tmpArray, tmpInt, tmpFloat);
        if (returnValue == 0) {
            textView.setText("Data Pass Success");
        } else {
            textView.setText("Data Pass Failed");
        }

    }

    public void onPassObjectToJNI(View view){
        TextView textView = findViewById(R.id.textViewPassObjectToJNI);

        SampleDataObj sampleDataObj = new SampleDataObj();
        sampleDataObj.setSampleInt(0);
        sampleDataObj.setSampleBoolean(true);
        sampleDataObj.setSampleString("Failed");

        // Pass data object to Native lib & get error code
        int ret = nativeLibrary.passObjectToJNI(sampleDataObj);

        if (ret == 0) {
            // if success, show updated values from JNI
            textView.setText(sampleDataObj.getSampleString());
        } else {
            //Failed
            textView.setText("FAILED");
        }

    }

    public void onGetObjectFromJNI(View view){
        TextView textView = findViewById(R.id.textViewGetObjectFromJNI);
        SampleDataObj dataObj = nativeLibrary.getObjectFromJNI();
        textView.setText(dataObj.getSampleString());
    }

    public void onCallBackFromJNIClicked(View view){
        nativeLibrary.callTheCallBackMethod();
    }

    /**
     * Callback event publisher
     *
     * @param data callback data
     */
    @Override
    public void callBackEvent(final String data) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                TextView textView = findViewById(R.id.textViewCallBackFromJNI);
                textView.setText(data);
            }
        });
    }
}