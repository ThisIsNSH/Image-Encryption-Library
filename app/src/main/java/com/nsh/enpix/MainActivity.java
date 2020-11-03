package com.nsh.enpix;

import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.widget.EditText;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.nsh.enpixview.EnpixView;

public class MainActivity extends AppCompatActivity {

    private EnpixView image1;
    private EditText grain;

    String key = "FirstnameLastnameEmailID@Something.com";

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        grain = findViewById(R.id.grain);

        image1 = findViewById(R.id.image1);
        image1.setImage(BitmapFactory.decodeResource(this.getResources(), R.drawable.pic3), key, Integer.parseInt(grain.getText().toString()), 100000);

    }


}

