Laboratório 4: Desempenho


Para vetores com 10^5 posições:


1 thread:
tempo sequencial: 0.003723
tempo concorrente: 0.008194
ganho de desempenho 0.454376

2 threads: 
tempo sequencial: 0.003693
tempo concorrente: 0.022537
ganho de desempenho 0.163846

4 threads:
tempo sequencial: 0.003723
tempo concorrente: 0.053177
ganho de desempenho 0.070014


Para vetores com 10^7 posições:


1 thread:
tempo sequencial: 0.233139
tempo concorrente: 0.504410
ganho de desempenho 0.462202

2 threads: 
tempo sequencial: 0.278992
tempo concorrente: 1.492813
ganho de desempenho 0.186890

4 threads:
tempo sequencial: 0.285919
tempo concorrente: 1.926849
ganho de desempenho 0.148387


Para vetores com 10^8 posições:


1 thread:
tempo sequencial: 2.240555
tempo concorrente: 4.416733
ganho de desempenho 0.507288

2 threads: 
tempo sequencial: 3.070374
tempo concorrente: 14.969116
ganho de desempenho 0.205114

4 threads:
tempo sequencial: 3.943604
tempo concorrente: 24.763092
ganho de desempenho 0.159253



obs: Não houve ganho de desempenho na parte concorrente do código, como observado nos testes.
