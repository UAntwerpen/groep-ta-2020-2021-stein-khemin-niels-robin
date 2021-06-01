# groep-ta-2020-2021-stein-khemin-niels-robin
Wij hebben een stadssimulatie gemaakt die de groei en evolutie van een stad voorspellen/simuleren. 
Dit hebben we gerealiseert met behulp van volgende features. Ten eerste hebben we de stad opgedeelt in verschillende soorten zones met verschillende soorten gebouwen. Doorheen deze zones kunnen mensen zich te voet of in een voertuig(auto) verplaatsen. Om de simulatie zo realistisch mogelijk te maken, hebben we een feature die dag en nacht zal implementeren en een feature die het verval van gebouwen en wegen zal implementeren. Om de simulatie grafisch te weergeven, gaan we gebruik maken van Qt. Dit zorgt ervoor dat we de gesimuleerde stad mooi in kaart kunnen brengen. Ten slotte zullen we deze implementaties met elkaar verbinden met een cellulaire automaat. 
Voor het maken van een stad hebben we gebruik gemaakt van een genetisch algoritme [2][3][4]. Dit genetisch algoritme heeft regels gemaakt die een realistische en goede stad maken.
Om de fitheid van een stad te bepalen hebben we formules opgestelt, die dus ook een effect hebben op hoe de stad eruitziet. Zo hebben we een blijheid toegevoegt aan de stad die op verschillende factoren let. Nadat de stad is opgesteld aan de hand van de geoptimaliseerde regels, hebben we bewoners toegevoegt om het leven in te stad te simuleren. Deze entiteiten zullen gebruik maken van een pathfinding algoritme [1] om hun gedrag meer realistisch voor te stellen.  
Het pathfinding algoritme beschouwt de cellen in de cellulaire automaat als muren of doorgangen. Alle doorgangen krijgen een willekeurige getalwaarde en iedere Goal heeft een getalwaarde van 0. De automaat volgt dan een aantal transities. Muren en Goals worden op zichzelf afgebeeld. Doorgangen nemen de waarde van hun laagste buur + 1 aan.

References

[1] https://www.slideshare.net/SteveWilson49/cellular-automata-for-pathfinding (vanaf dia 80)\
[2] https://www.youtube.com/watch?v=sfmucBj-v00&ab_channel=ComplexityExplorer \
[3] https://www.youtube.com/watch?v=nhT56blfRpE&ab_channel=KieCodes \
[4] https://www.youtube.com/watch?v=uQj5UNhCPuo&ab_channel=KieCodes 
