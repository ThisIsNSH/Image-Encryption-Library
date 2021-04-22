package com.nsh.enpix;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import com.nsh.enpixview.EnpixView;

import java.security.NoSuchAlgorithmException;

public class MainActivity extends AppCompatActivity {

    private EnpixView image1, image2;

    String key = "firstname.lastname@email.com-nameofuser-mobilenumber";

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        image1 = findViewById(R.id.image1);
        image2 = findViewById(R.id.image2);

        try {
            long time = System.currentTimeMillis();
            Bitmap im = image1.getEncryptImage(this, BitmapFactory.decodeResource(this.getResources(), R.drawable.pic3), key, 10000000);
            image1.setImageBitmap(im);
            image2.decryptImage(this, im, key, 10000000);
            System.out.println(System.currentTimeMillis() - time);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }

    }


}

//7141
//17449