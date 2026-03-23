package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "JNI_MAIN";

    public native String helloFromJNI();
    public native int factorial(int n);
    public native String reverseString(String s);
    public native int sumArray(int[] values);
    public native long heavyTaskNative(int iterations);

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvHello = findViewById(R.id.tvHello);
        TextView tvFact1 = findViewById(R.id.tvFact1);
        TextView tvFact2 = findViewById(R.id.tvFact2);
        TextView tvFact3 = findViewById(R.id.tvFact3);
        TextView tvReverse1 = findViewById(R.id.tvReverse1);
        TextView tvReverse2 = findViewById(R.id.tvReverse2);
        TextView tvArray1 = findViewById(R.id.tvArray1);
        TextView tvArray2 = findViewById(R.id.tvArray2);
        TextView tvBenchmark = findViewById(R.id.tvBenchmark);

        // 1. Hello
        tvHello.setText(helloFromJNI());

        // 2. Factoriels avec TRY/CATCH (Gestion d'exception native)
        tvFact1.setText("Fact(10) = " + factorial(10));

        try {
            factorial(-5);
        } catch (IllegalArgumentException e) {
            tvFact2.setText("Fact(-5) -> Erreur catchée : " + e.getMessage());
        }

        try {
            factorial(20);
        } catch (IllegalArgumentException e) {
            tvFact3.setText("Fact(20) -> Erreur catchée : " + e.getMessage());
        }

        // 3. Strings & Arrays (Normaux)
        tvReverse1.setText("Reverse('JNI is powerful!') = " + reverseString("JNI is powerful!"));
        tvReverse2.setText("Reverse('') = '" + reverseString("") + "'");
        
        int[] nums = {10, 20, 30, 40, 50};
        tvArray1.setText("Somme({10..50}) = " + sumArray(nums));

        try {
            sumArray(null);
        } catch (IllegalArgumentException e) {
            tvArray2.setText("Somme(null) -> Erreur catchée : " + e.getMessage());
        }

        // 4. Benchmark Extension
        runBenchmark(tvBenchmark);
    }

    private void runBenchmark(TextView tv) {
        int iterations = 10_000_000;

        // Temps Java
        long startJava = System.currentTimeMillis();
        long resJava = heavyTaskJava(iterations);
        long timeJava = System.currentTimeMillis() - startJava;

        // Temps Natif
        long startNative = System.currentTimeMillis();
        long resNative = heavyTaskNative(iterations);
        long timeNative = System.currentTimeMillis() - startNative;

        tv.setText(String.format("Benchmark (%d itérations) :\nJava: %dms | Natif: %dms\nGain: %.1fx", 
                   iterations, timeJava, timeNative, (double)timeJava/timeNative));
    }

    private long heavyTaskJava(int iterations) {
        long sum = 0;
        for (int i = 0; i < iterations; i++) {
            sum += (i % 100);
        }
        return sum;
    }
}