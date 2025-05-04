![Visitors](https://visitor-badge.laobi.icu/badge?page_id=hasanaliozkan-dev/GeneticAlgorithms)

## Genetik Algoritmalar Nedir?

Genetik algoritmalar daha geniş ismi ile Evrimsel Hesaplama biyoloji bilimindeki genetik konusunun teorik olarak bilgisayar bilimlerinde bir takım problemleri çözmek için uygulanması sonucu ortaya çıkan algoritmalardır.  Bir başka deyişle genetik algoritmalar tıpkı doğadaki evrimsel süreçler gibi bir popülasyon üzerinde genetik operasyonlar(mutasyon, doğal seçilim vb.) eşliğinde  rassal düzenlemerle en iyi sonucu elde etmek için kullanılan algoritmalardır.  Genetik algoritmalar az sayıda veri ile çok hızlı sonuçlar üretebilirken çözüm kümesinde lokal en iyi değerlerine takılma olasılıkları yüksek algoritmalardır.  Genetik algoritmalar ilk kez 1975 yılında biyolog bir mühendis olan Holland tarafından kullanılmıştır.[1] 

## Genetik Algoritmaların Çalışma Alanları Nelerdir?

Genetik algoritmalar bir çok alana uygulanabilmektedir. Bu alanların başında optimizasyon problemleri gelmektedir. Her optimizasyon probleminde optimum değerleri bulmak için genetik algoritmalardan faydalanılabilir. Yol ver rota planlamalarında sezgisel olarak en kısa rotayı bulmak için genetik algoritmalardan faydalanılır. Biyo-informatik alanında gen dizilimlerini oluşturmak için genetik algoritmalardan faydalanılabilir. Oyun geliştirmede yan karakterlerin hareketlerini ve optimizasyonunu sağlamak için de genetik algoritmalardan faydalanılabilir. Son zamanlarda çok konuşulan makine öğrenimi ve yapay zeka alanlarında da bir çok problem için genetik algoritmalar kullanılmaktadır. Örneğin yine Holland tarafından ortaya sürülen Öğrenme Sınıflandırma Sistemi(LCS) sınıflandırma problemlerinde kullanılırken aynı zamanda genetik algoritmalar kullanılarak diğer makine öğrenmesi algoritmaları optimize edilebilir[2]. Sadece model  eğitme aşamasında değil aynı zamanda genetik algoritmalar veri ön işleme aşamalarında da kullanılabilen algoritmalardır örneğin az veri bulunan veri setlerinde eksik veri doldurma işlemlerinde genetik algoritmaların istatistik temelli eksik veri doldurma çözümleri ya da makine öğrenmesi ile eksik veri doldurma çözümlerine kıyasla daha iyi sonuçlar verdiği görülmektedir [3].  

## Genetik Algoritmaların Çalışma Prensibi

Genetik algoritmaları tanımlarken de dediğim gibi temel prensip doğadaki evrimsel süreçleri taklit etmektir. Genetik algoritma ile bir problem çözmek istiyorsanız öncelikle bir çözüm kümeniz olması gerekli ve bu kümenin içerisinde de potansiyel optimum çözümler. Bu küme terminolojide ***Popülasyon (population)***  diye geçmekte.  Bazı uygulamalarda popülasyon rastgele oluşturulurken bazı uygulamalarda ise veri setine sadık kalınarak belirli parametreler göz önünde bulundurularak oluşturulur.  Popülasyonun içerisindeki her bir potansiyel optimum çözüme de ***birey (individual)*** diyoruz. Her birey bir dizi çözümü temsil eder her bir çözümde ***genomdur.*** Genomları çözümler için kodlanmış parametreler olarak düşünebiliriz. Popülasyon büyüklüğü problemden probleme değişiklik gösterebilir ama çok büyük popülasyonlar büyük hacimlerde işlemler gerektireceği için işlem maliyeti bakımından pek önerilmez. Çok küçük popülasyonlarında yerel en iyiye takılma ihtimalleri oldukça yüksektir. **Popülasyon oluşturulduktan sonra optimum çözümleri bulabilmek için probleme özgü bir ***uygunluk değerlendirmesi (fitness evaluation)***  belirlenmelidir. Belirlelenen bu değer her bir birey için hesaplanır ve bireyler uygunluk değerlerine göre ya elenir ya da bir sonraki nesile aktarılmayı başarır. Burada bir eşik değeri hesaplanır ve eşik değerinin üzerindeki bireyler bir sonraki nesile aktarılır bu işlemin adı ***Seçilim(Selection)’***dir*.* Seçilim daha yüksek uygunluk değerine sahip bireylerin sonraki nesillerde daha yüksek üreme oranlarına sahip olmalarını sağlar. Seçilim işlemi bir kaç farklı şekilde gerçekleştirilebilir, en çok bilinenleri ***elitizim*** (***elitism) , rulet yöntemi (roulette method) , turnuva seçilimi (tournament selection).*** Elitizm en çok uygunluk değerine sahip sınırlı sayıdaki bireylerin bir sonraki nesile aktarılmasını sağlar.  Turnuva seçiliminde ise popülasyondan rastgele seçilmiş bireyler üzerinde uygunluk değerleri karşılaştırılır ve en uygun olan bir sonraki nesile aktarılır. Bu işlem içerisinde rastgelelik olduğu için belki de iki kötü birey arasından daha az kötü olan bir sonraki nesile aktarılma ihtimalini içerisinde barındırır. Rulet yönteminde de her bir birey için uygunluk değerleri normalize edilir ve uygunluk skorları azalacak şekilde bireyler sıralanır. Normalizasyon işlemi her bir bireyin uygunluk değerinin nüfustaki uygunluk değerlerinin toplamına bölünmesiyle gerçekleşir. Sonrasında 0 ile 1 arasında rastgele bir sayı seçilir ve uygunluk değeri bu sayıdan büyük olan ilk birey bir sonraki nesile aktarılır. Bir sonraki aşamada ***çaprazlama (crossover)*** yapılır. Çaprazlama bir ya da birden fazla genomun rastgele seçilen iki birey arasında yine rastgele bir noktadan değişmesidir.  Seçilim tamamlandıktan sonra çaprazlama uygulanır ve bir sonraki aşama olan ***mutasyon(mutation)*** aşamasına geçilir. Bu aşamada rastgele seçilen genomlar yine rastgele atanmış değerlerle değiştirilir. Çaprazlama ve mutasyon genetik çeşitliliği arttırır. Çaprazlama ve mutasyon olasılıkları algoritmanın parametreleridir. Tüm bu genetik süreç istenilen nesil kadar ya da bir uygunluk eşik değerine ulaşana kadar tekrar eder. Bu döngü bittikten sonra en iyi birey problem için en uygun çözüm olarak kabul edilir.

```
t ← 0
Popülasyon P(t) ← Rastgele N birey oluştur
Her birey için uygunluk değerini hesapla: f(x)

Tekrar et (t < max_nesil veya durma_kriteri_saglandi() değilse):
   Yeni popülasyon P_yeni ← ∅

   Elitizm uygula (isteğe bağlı):  - En iyi birey(leri) P_yeni'ye kopyala
	 Seçim işlemi:
   P(t)'den iki ebeveyn seç: Parent1, Parent2 ← seçim_yöntemi(P(t))

   Çaprazlama işlemi:
   Eğer rand() < çaprazlama_olası:
       Child1, Child2 ← crossover(Parent1, Parent2)
    Aksi halde:
       Child1 ← Parent1, Child2 ← Parent2

   Mutasyon işlemi:
      - Child1 ← mutate(Child1)
      - Child2 ← mutate(Child2)

   P_yeni’ye çocukları ekle

   Eğer P_yeni boyutu < N ise c–f adımlarını tekrarla

   Yeni bireyler için fitness hesapla

   Popülasyonu güncelle:
      - P(t+1) ← P_yeni
      - t ← t + 1
Çıkış:
   - En iyi birey ve onun uygunluk değeri f(x) döndürülür
```
## Örnek Bir Uygulama

Basit bir genetik algoritmayı yazdığım Github Repo’ma buradan ulaşabilirsiniz. Buradaki amaç “Hello World” cümlesini oluşturabilmektir. Aşağıda her bir adımı bu örnek üzerinden anlatacağım. 

**Gen (Genom) :** Her bir karakter. 

**Birey (Individual) :** 11 karakterden oluşan karakter dizisi.

**Popülasyon (Population) :** Belirli sayıda birey barındıran liste. Bu örnek için bu sayı 100.

**Uygunluk Fonksiyonu (Fitness Function):** Bu örnekte bireyin herhangi bir noktadaki karakteri ile hedef karakter dizinindeki karakter aynı ise uygunluk skorunu arttırıyoruz.

**Çaprazlama (Crossover):** Çaprazlama aşamasında ilk başta çaprazlama olasılığına göre çaprazlama yapıp yapmamaya karar veriyoruz sonrasında eğer çaprazlama yapacaksak rastgele noktalarda çaprazlama yani genom değişimi gerçekleşiyor.

**Mutasyon (Mutation):** Mutasyon aşamasında yine ilk başta mutasyon olasılığına bakıyoruz ve eğer mutasyon gerçekleşecekse rastgele bir karakteri(geni) rastgele başka bir karakter(gen) ile değiştiriyoruz.

Son olarak eğer herhangi bir nesilde ***“Hello World”***  oluşmuş ise algoritma orada duruyor ve hangi bireyde yakaladığı ekrana yazdırıyor. Eğer herhangi bir nesilde oluşmaz ise algoritma 1000 kez çalışıp ardından duruyor.

Repoyu kendi bilgisayarınıza indirip farklı parametreler ile deneyebilirsiniz aynı zamanda farklı metinlerde ürettirebilirsiniz.

## Referanslar
1. *Adaptation in Natural and Artificial Systems* (1975, MIT Press)
2. Bull, L. (2004). Learning classifier systems: A brief introduction. In *Applications of learning classifier systems* (pp. 1-12). Berlin, Heidelberg: Springer Berlin Heidelberg.
3. Figueroa-García, J. C., Neruda, R., & Hernandez–Pérez, G. (2023). A genetic algorithm for multivariate missing data imputation. *Information Sciences*, *619*, 947-967.
