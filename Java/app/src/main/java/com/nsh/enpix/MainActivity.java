package com.nsh.enpix;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

public class MainActivity extends AppCompatActivity {

    private Spinner spinner1, spinner2, spinner3;
    private ImageView image1, image2, image3;
    private EditText grain;

    String key = "Gauravgauravsirav2399@gmail.com9079035112";

    List<String> names = new ArrayList<>();
    List<String> emails = new ArrayList<>();
    List<String> numbers = new ArrayList<>();

    int dekey0 = 0;
    int dekey1 = 0;
    int dekey2 = 0;

    Bitmap pic1;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinner1 = findViewById(R.id.spinner1);
        spinner2 = findViewById(R.id.spinner2);
        spinner3 = findViewById(R.id.spinner3);

        grain = findViewById(R.id.grain);

        image1 = findViewById(R.id.image1);

        names.add("Nishant");
        names.add("Kashif");
        names.add("Gaurav");

        emails.add("hadanis.singh@gmail.com");
        emails.add("kashifsyed402266@gmail.com");
        emails.add("gauravsirav2399@gmail.com");

        numbers.add("9560705734");
        numbers.add("9857733786");
        numbers.add("9079035112");

        findViewById(R.id.button1).setOnClickListener(v -> {
            encryptImg(Integer.parseInt(String.valueOf(grain.getText())));
        });

        findViewById(R.id.button2).setOnClickListener(v -> {
            decryptImg(Integer.parseInt(String.valueOf(grain.getText())));
        });

        ArrayAdapter aa1 = new ArrayAdapter(this, android.R.layout.simple_spinner_item, names);
        ArrayAdapter aa2 = new ArrayAdapter(this, android.R.layout.simple_spinner_item, emails);
        ArrayAdapter aa3 = new ArrayAdapter(this, android.R.layout.simple_spinner_item, numbers);

        aa1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        aa2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        aa3.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spinner1.setAdapter(aa1);
        spinner2.setAdapter(aa2);
        spinner3.setAdapter(aa3);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public void encryptImg(int grain) {

        Bitmap temp = BitmapFactory.decodeResource(this.getResources(), R.drawable.pic3);
        pic1 = Bitmap.createBitmap(temp.getWidth(), temp.getHeight(), Bitmap.Config.ARGB_8888);
        Bitmap temp1 = Bitmap.createBitmap(temp.getWidth(), temp.getHeight(), Bitmap.Config.ARGB_8888);

        String base64 = encrypt(key, "1/9/2020/10/10");
        System.out.println(base64);

        int len1 = base64.length();
        int len2 = temp.getWidth();

        if (len2 < len1) {
            base64 = base64.substring(0, len2);
        } else if (len2 > len1) {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < len2 / len1; i++) {
                s.append(base64);
            }
            s.append(base64);
            base64 = s.toString().substring(0, len2);
        }

        StringBuilder sb = new StringBuilder();

        HashSet<Integer> set = new HashSet<>();
        int max = temp.getWidth() / grain;

        for (char c : base64.toCharArray()) {
            sb.append((int) c);
        }

        char[] ch = sb.toString().toCharArray();

        for (int i = 0; i < ch.length; i++) {
            StringBuilder sb1 = new StringBuilder();
            for (int j = i; j < ch.length; j++) {
                sb1.append(ch[j]);
                int k = Integer.parseInt(sb1.toString());
                if (k < max) {
                    if (set.add(k)) break;
                } else {
                    while (k >= max || (k >= 0 && !set.add(k))) {
                        k--;
                    }
                    break;
                }
            }
            if (set.size() == max) break;
        }

        for (int i = 0; i < temp.getWidth() / grain; i++) {
            set.add(i);
        }

        int col = 0;
        for (Integer k : set) {
            int num = k * grain;
            for (int i = 0; i < grain; i++) {
                for (int j = 0; j < temp.getHeight(); j++) {
                    int px = temp.getPixel(num + i, j);
                    temp1.setPixel(col, j, px);
                }
                col++;
            }
        }

        len1 = base64.length();
        len2 = temp.getHeight();

        if (len2 < len1) {
            base64 = base64.substring(0, len2);
        } else if (len2 > len1) {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < len2 / len1; i++) {
                s.append(base64);
            }
            s.append(base64);
            base64 = s.toString().substring(0, len2);
        }

        sb = new StringBuilder();

        set = new HashSet<>();
        max = temp.getHeight() / grain;

        for (char c : base64.toCharArray()) {
            sb.append((int) c);
        }

        ch = sb.toString().toCharArray();

        for (int i = 0; i < ch.length; i++) {
            StringBuilder sb1 = new StringBuilder();
            for (int j = i; j < ch.length; j++) {
                sb1.append(ch[j]);
                int k = Integer.parseInt(sb1.toString());
                if (k < max) {
                    if (set.add(k)) break;
                } else {
                    while (k >= max || (k >= 0 && !set.add(k))) {
                        k--;
                    }
                    break;
                }
            }
            if (set.size() == max) break;
        }

        for (int i = 0; i < temp.getHeight() / grain; i++) {
            set.add(i);
        }

        int row = 0;
        for (Integer k : set) {
            int num = k * grain;
            for (int i = 0; i < grain; i++) {
                for (int j = 0; j < temp1.getWidth(); j++) {
                    int px = temp1.getPixel(j, num + i);
                    pic1.setPixel(j, row, px);
                }
                row++;
            }
        }

        image1.setImageBitmap(pic1);

    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public void decryptImg(int grain) {

//        String base64 = encrypt((names.get(dekey0) + emails.get(dekey1) + numbers.get(dekey2)), "11/10/2020/19/30");

        Bitmap temp1 = Bitmap.createBitmap(pic1.getWidth(), pic1.getHeight(), Bitmap.Config.ARGB_8888);
        Bitmap pic2 = Bitmap.createBitmap(pic1.getWidth(), pic1.getHeight(), Bitmap.Config.ARGB_8888);

        String base64 = encrypt(key, "1/9/2020/10/10");
        System.out.println(base64);

        int len1 = base64.length();
        int len2 = pic1.getHeight();

        if (len2 < len1) {
            base64 = base64.substring(0, len2);
        } else if (len2 > len1) {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < len2 / len1; i++) {
                s.append(base64);
            }
            s.append(base64);
            base64 = s.toString().substring(0, len2);
        }

        StringBuilder sb = new StringBuilder();

        HashSet<Integer> set = new HashSet<>();
        int max = pic1.getHeight() / grain;

        for (char c : base64.toCharArray()) {
            sb.append((int) c);
        }

        char[] ch = sb.toString().toCharArray();

        for (int i = 0; i < ch.length; i++) {
            StringBuilder sb1 = new StringBuilder();
            for (int j = i; j < ch.length; j++) {
                sb1.append(ch[j]);
                int k = Integer.parseInt(sb1.toString());
                if (k < max) {
                    if (set.add(k)) break;
                } else {
                    while (k >= max || (k >= 0 && !set.add(k))) {
                        k--;
                    }
                    break;
                }
            }
            if (set.size() == max) break;
        }

        for (int i = 0; i < pic1.getHeight() / grain; i++) {
            set.add(i);
        }

        int row = 0;
        for (Integer k : set) {
            int num = k * grain;
            for (int i = 0; i < grain; i++) {
                for (int j = 0; j < pic1.getWidth(); j++) {
                    int px = pic1.getPixel(j, row);
                    temp1.setPixel(j, num + i, px);
                }
                row++;
            }
        }

        len1 = base64.length();
        len2 = pic1.getWidth();

        if (len2 < len1) {
            base64 = base64.substring(0, len2);
        } else if (len2 > len1) {
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < len2 / len1; i++) {
                s.append(base64);
            }
            s.append(base64);
            base64 = s.toString().substring(0, len2);
        }

        sb = new StringBuilder();

        set = new HashSet<>();
        max = pic1.getWidth() / grain;

        for (char c : base64.toCharArray()) {
            sb.append((int) c);
        }

        ch = sb.toString().toCharArray();

        for (int i = 0; i < ch.length; i++) {
            StringBuilder sb1 = new StringBuilder();
            for (int j = i; j < ch.length; j++) {
                sb1.append(ch[j]);
                int k = Integer.parseInt(sb1.toString());
                if (k < max) {
                    if (set.add(k)) break;
                } else {
                    while (k >= max || (k >= 0 && !set.add(k))) {
                        k--;
                    }
                    break;
                }
            }
            if (set.size() == max) break;
        }

        for (int i = 0; i < pic1.getWidth() / grain; i++) {
            set.add(i);
        }

        int col = 0;
        for (Integer k : set) {
            int num = k * grain;
            for (int i = 0; i < grain; i++) {
                for (int j = 0; j < temp1.getHeight(); j++) {
                    int px = temp1.getPixel(col, j);
                    pic2.setPixel(num + i, j, px);
                }
                col++;
            }
        }

        image1.setImageBitmap(pic2);
    }

    private static SecretKeySpec secretKey;

    public static void setKey(String myKey) {
        byte[] key;
        MessageDigest sha = null;
        try {
            key = myKey.getBytes("UTF-8");
            sha = MessageDigest.getInstance("SHA-1");
            key = sha.digest(key);
            key = Arrays.copyOf(key, 16);
            secretKey = new SecretKeySpec(key, "AES");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public static String encrypt(String strToEncrypt, String secret) {
        try {
            setKey(secret);
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
            byte[] arr = cipher.doFinal(strToEncrypt.getBytes("UTF-8"));
            return android.util.Base64.encodeToString(arr, arr.length);
        } catch (Exception e) {
            System.out.println("Error while encrypting: " + e.toString());
        }
        return null;
    }

    static int getMax(int arr[], int n) {
        int mx = arr[0];
        for (int i = 1; i < n; i++)
            if (arr[i] > mx)
                mx = arr[i];
        return mx;
    }

    static void countSort(int arr[], int n, int exp) {
        int output[] = new int[n]; // output array
        int i;
        int count[] = new int[10];
        Arrays.fill(count, 0);

        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++)
            arr[i] = output[i];
    }

    static void radixsort(int arr[], int n) {
        int m = getMax(arr, n);

        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, n, exp);
    }

}

