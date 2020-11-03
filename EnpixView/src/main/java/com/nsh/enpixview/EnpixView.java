package com.nsh.enpixview;

import android.content.Context;
import android.graphics.Bitmap;
import android.os.Build;
import android.util.AttributeSet;

import androidx.annotation.RequiresApi;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.HashSet;

import javax.crypto.spec.SecretKeySpec;

public class EnpixView extends androidx.appcompat.widget.AppCompatImageView {

    public EnpixView(Context context) {
        super(context);
    }

    public EnpixView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public EnpixView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public void setImage(Bitmap bitmap, String key, int grain, int time) {
        setImageBitmap(decryptImg(bitmap, key, grain, time));
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public Bitmap encryptImg(Bitmap temp, String key, int grain, int time) {

        Bitmap pic1 = Bitmap.createBitmap(temp.getWidth(), temp.getHeight(), Bitmap.Config.ARGB_8888);
        Bitmap temp1 = Bitmap.createBitmap(temp.getWidth(), temp.getHeight(), Bitmap.Config.ARGB_8888);

        String base64 = encrypt(key, String.valueOf(System.currentTimeMillis() / time));

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

        return pic1;
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public Bitmap decryptImg(Bitmap pic1, String key, int grain, int time) {

        Bitmap temp1 = Bitmap.createBitmap(pic1.getWidth(), pic1.getHeight(), Bitmap.Config.ARGB_8888);
        Bitmap pic2 = Bitmap.createBitmap(pic1.getWidth(), pic1.getHeight(), Bitmap.Config.ARGB_8888);

        String base64 = encrypt(key, String.valueOf(System.currentTimeMillis() / time));

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

        return pic2;
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
//            setKey(secret);
//            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
//            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
//            byte[] arr = cipher.doFinal(strToEncrypt.getBytes("UTF-8"));
            byte[] arr = strToEncrypt.getBytes("UTF-8");
            return android.util.Base64.encodeToString(arr, arr.length);
        } catch (Exception e) {
            System.out.println("Error while encrypting: " + e.toString());
        }
        return null;
    }


}
