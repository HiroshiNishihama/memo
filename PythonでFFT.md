# PythonでFFTをする

```python
import numpy as np
import matplotlib.pyplot as plt

def FFT(src, window="hanning"):
    N = len(src)
    # 窓関数を作成
    if window == "hanning":
        wf = np.hanning(N)
    elif window == "hamming":
        wf = np.hamming(N)
    elif window == "blackman":
        wf = np.blackman(N)
    else:
        wf = None
    
    # 入力信号と窓関数を乗算する
    if type(wf) == np.ndarray:
        src_windowed = src * wf
        acf = 1/(sum(wf)/N)
    else:
        src_windowed = src
        acf = 1.0
    fftdata = np.fft.fft(src_windowed)
    return fftdata, acf

def ABS(fftdata, dt, acf):
    N = len(fftdata)
    # AMP計算
    F_abs = np.abs(fftdata)
    F_abs_amp = F_abs / N * 2
    F_abs_amp[0] /= 2
    fq = np.linspace(0, 1.0/dt, N)
    # 窓補正
    F_abs_amp = F_abs_amp * acf
    # ナイキスト定数まで抽出
    fq_out = fq[:int(N/2)+1]
    F_abs_amp_out = F_abs_amp[:int(N/2)+1]
    return [fq_out, F_abs_amp_out]

### 入力データ
a = 0.2     #振幅
fs = 8000 #サンプリング周波数
f0 = 1000  #周波数
f1 = 1333
sec = 5   #秒
 
t = np.arange(0, sec, 1/fs)
swav = a * np.sin(2.0 * np.pi * f0 * t) + 2.0
swav = swav + 1.0 * np.cos(2.0 * np.pi * f1 * t)
swav = swav + (np.random.random_sample(len(swav))*15.0)
    
#サイン波を表示
plt.plot(swav[0:100])
plt.show()

### FFTを実行して結果をプロットする
fft_data, acf = FFT(swav,window="blackman")
amp = ABS(fft_data,1.0/fs,acf)
print(amp)
fig, ax = plt.subplots()
ax.plot(amp[0][4500:5500],amp[1][4500:5500])
ax.set_xlabel("Freqency [Hz]")
ax.set_ylabel("Amplitude")
ax.grid()
plt.show()

```
