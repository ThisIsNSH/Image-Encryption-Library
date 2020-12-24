package com.nsh.enpix;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.nsh.enpixview.EnpixView;

import java.security.NoSuchAlgorithmException;

public class MainActivity extends AppCompatActivity {

    private EnpixView image1;
    private EditText grain;
    private Button button1, button2;

    String key = "firstname.lastname@email.com-nameofuser-mobilenumber";
    Bitmap bmp;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        grain = findViewById(R.id.grain);
        button1 = findViewById(R.id.button1);
        button2 = findViewById(R.id.button2);

        image1 = findViewById(R.id.image1);
        bmp = BitmapFactory.decodeResource(this.getResources(), R.drawable.pic3);

        button1.setOnClickListener(v->{
            try {
                bmp = image1.getEncryptImage(bmp, key, 1000000);
                image1.setImageBitmap(bmp);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        });

        button2.setOnClickListener(v->{
            try {
                bmp = image1.getDecryptImage(bmp, key, 1000000);
                image1.setImageBitmap(bmp);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        });

    }


}

