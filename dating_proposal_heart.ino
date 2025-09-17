#include <SPI.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <TFT_eSPI.h>
#include "heart.h"

#define DISPLAY_W 320
#define DISPLAY_H 170

const byte DNS_PORT = 53;
const String ssid = "{{BOYFRIEND}} ❤ {{GIRLFRIEND}}";
const String password = "";
IPAddress apIP(8,8,4,4); // The default android DNS
DNSServer dnsServer;
WiFiServer server(80);
TFT_eSPI tft = TFT_eSPI();

void setup() {
  digitalWrite(38, 0);

  // Init TFT
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setTextFont(1);

  // Init WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  WiFiClient client = server.available(); // listen for incoming clients

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // Split html into chunks of 8192 bytes
            client.print("<!doctype html><html lang=pt-BR><head><meta charset=UTF-8><meta name=viewport content=\"width=device-width,initial-scale=1\"><title>Quer namorar comigo?</title><style>:root{--icon-size:300px;--color-neutral-100:#AAB8C2;--color-neutral-200:#A3B1BA;--color-red-100:#E2264D;--color-red-200:#F48EA7;--color-purple-100:#CC8EF5;--color-purple-200:#D46ABF;--color-purple-300:#DD4688;--color-blue-100:#9FC7FA;--color-green-100:#9CD8C3;--motion-speed-exit:0.15s;--motion-speed-hover:0.2s}body,html{background-color:#1a1a1a;margin:0;padding:0;overflow:hidden;max-height:100vh}.stars{position:absolute;top:0;left:0;width:100%;height:100%;overflow:hidden}#stars1,#stars2,#stars3{position:absolute;background:0 0;border-radius:50%;animation:animateStars 100s linear infinite}#stars1{width:1px;height:1px;box-shadow:796px 1640px #fff,1508px 233px #fff,882px 1445px #fff,1283px 113px #fff,143px 1032px #fff,811px 1199px #fff,110px 1061px #fff,1106px 144px #fff,65px 121px #fff,1694px 926px #fff,1024px 132px #fff,88px 973px #fff,1947px 1675px #fff,137px 555px #fff,149px 1275px #fff,1618px 117px #fff,1530px 131px #fff,1294px 791px #fff,854px 1475px #fff,622px 135px #fff,1872px 1335px #fff,1374px 1162px #fff,626px 1419px #fff,1302px 531px #fff,1144px 1307px #fff,1204px 1146px #fff,180px 1827px #fff,151px 713px #fff,1461px 1974px #fff,883px 1833px #fff,154px 1298px #fff,429px 1633px #fff,1056px 1134px #fff,1588px 1473px #fff,1754px 140px #fff,126px 1586px #fff,1849px 695px #fff,1283px 1916px #fff,45px 1606px #fff,545px 1010px #fff,104px 1921px #fff,1354px 186px #fff,1507px 108px #fff,241px 1283px #fff,1600px 1848px #fff,1171px 192px #fff,1149px 1215px #fff,188px 167px #fff,143px 127px #fff,1488px 339px #fff,1198px 1038px #fff,1982px 703px #fff,32px 1682px #fff,1729px 1668px #fff,1493px 1015px #fff,93px 641px #fff,1539px 1413px #fff,1884px 1421px #fff,1136px 878px #fff,1690px 1845px #fff,1439px 1076px #fff,1452px 1083px #fff,1625px 89px #fff,1917px 1102px #fff,1021px 1853px #fff,599px 1133px #fff,1324px 1013px #fff,1102px 1876px #fff,165px 1957px #fff,1246px 1341px #fff,1934px 1866px #fff,1832px 1415px #fff,1589px 1313px #fff,1769px 729px #fff,436px 1293px #fff,1623px 1937px #fff,1515px 1358px #fff,1877px 461px #fff,174px 1007px #fff,80px 1854px #fff,1609px 1119px #fff,417px 534px #fff,1109px 1317px #fff,1218px 1131px #fff,599px 1148px #fff,1262px 1022px #fff,1229px 1912px #fff,1221px 198px #fff,1541px 1213px #fff,1471px 956px #fff,1144px 1954px #fff,692px 167px #fff,1436px 1176px #fff,1699px 1317px #fff,1853px 406px #fff,1865px 443px #fff;animation-duration:250s}#stars2{width:2px;height:2px;box-shadow:1735px 1563px #fff,532px 1108px #fff,182px 1543px #fff,762px 1710px #fff,299px 791px #fff,1502px 138px #fff,752px 1152px #fff,1033px 1342px #fff,1103px 485px #fff,107px 179px #fff,1238px 1475px #fff,576px 1075px #fff,1618px 446px #fff,1269px 1313px #fff,1528px 276px #fff,100px 933px #fff,962px 113px #fff,1372px 282px #fff,1686px 1059px #fff,1779px 1518px #fff,1599px 1259px #fff,1281px 1386px #fff,1041px 1009px #fff,796px 177px #fff,163px 188px #fff,1572px 790px #fff,1005px 1700px #fff,246px 1376px #fff,1505px 1869px #fff,1038px 1195px #fff,895px 1380px #fff,162px 1195px #fff,1115px 129px #fff,459px 1888px #fff,109px 1162px #fff,105px 1030px #fff,513px 1151px #fff,218px 1756px #fff,1813px 1289px #fff,1381px 1645px #fff,1210px 1022px #fff,1262px 1421px #fff,1616px 1017px #fff,273px 110px #fff,321px 1110px #fff,1078px 843px #fff,1787px 299px #fff,1002px 343px #fff,1861px 1749px #fff,959px 1279px #fff;animation-duration:200s}#stars3{width:3px;height:3px;box-shadow:1063px 1806px #fff,793px 1241px #fff,160px 1012px #fff,1819px 1119px #fff,1512px 1648px #fff,143px 1971px #fff,1667px 1149px #fff,1146px 1566px #fff,1339px 105px #fff,1020px 79px #fff,1320px 229px #fff,452px 1056px #fff,175px 1152px #fff,1800px 117px #fff,281px 1384px #fff,1475px 826px #fff,1799px 1656px #fff,1507px 1640px #fff,1434px 175px #fff,1485px 502px #fff;animation-duration:150s}@keyframes animateStars{from{transform:translateY(0)}to{transform:translateY(-2000px)}}.content{display:flex;width:100vw;height:100vh;flex-direction:column;align-items:center;justify-content:center;position:relative;z-index:10}.text-container{position:relative;height:80px;margin-bottom:20px;width:100%}.dating-request,.love-message{font-family:sans-serif;text-align:center;color:#f3faff;font-size:2rem;user-select:none;transition:opacity .4s ease-in-out,transform .4s ease-in-out;width:100%;position:absolute;left:0;top:0}.love-message{opacity:0;transform:translateY(20px);color:var(--color-red-200);font-size:2.5rem}.notice{font-family:sans-serif;text-align:center;color:#f3faff;font-size:.9rem;user-select:none;transition:opacity .3s ease}.notice span{font-size:1rem;color:var(--color-red-100);text-transform:uppercase;font-weight:700}.anicon-heart__svg{cursor:pointer;overflow:visible;width:var(--icon-size)}.anicon-heart__heart{fill:var(--color-neutral-100);transform-origin:center;animation:animateHeartExit var(--motion-speed-exit) linear forwards}.anicon-heart__heart:hover{fill:var(--color-neutral-200);transition:fill var(--motion-speed-hover) ease}.anicon-heart__circ{transform-origin:29.5px 29.5px}.anicon-heart__checkbox{display:none}#checkbox:checked~.text-container .dating-request{opacity:0;transform:translateY(-20px)}#checkbox:checked~.text-container .love-message{opacity:1;transform:translateY(0);transition-delay:0.2s}#checkbox:checked~.anicon-heart .notice{opacity:0}#checkbox:checked~.anicon-heart label .anicon-heart__heart{transform:scale(.2);fill:var(--color-red-100);animation:animateHeartEnter .3s ease-in forwards .25s}#checkbox:checked~.anicon-heart label .anicon-heart__circ{transition:all 2s;animation:animateCircle .3s ease-in forwards;opacity:1}#checkbox:checked~.anicon-heart label .anicon-heart__group1{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group1 .ani-heart__dot1{transform:scale(0) translate(0,-30px);transform-origin:0 0 0;transition:.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group1 .ani-heart__dot2{transform:scale(0) translate(10px,-50px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group2{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group2 .ani-heart__dot1{transform:scale(0) translate(60px,-15px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group2 .ani-heart__dot2{transform:scale(0) translate(30px,-15px);transform-origin:0 0 0;transition:.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group3{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group3 .ani-heart__dot1{transform:scale(0) translate(60px,10px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group3 .ani-heart__dot2{transform:scale(0) translate(30px,0);transform-origin:0 0;transition:.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group4{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group4 .ani-heart__dot1{transform:scale(0) translate(30px,15px);transform-origin:0 0;transition:.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group4 .ani-heart__dot2{transform:scale(0) translate(40px,50px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group5{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group5 .ani-heart__dot1{transform:scale(0) translate(-10px,20px);transform-origin:0 0 0;transition:.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group5 .ani-heart__dot2{transform:scale(0) translate(-60px,30px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group6{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group6 .ani-heart__dot1{transform:scale(0) translate(-30px,0);transform-origin:0 0 0;transition:.5s transform .3s}#checkbox:checked");
            client.print("~.anicon-heart label .anicon-heart__group6 .ani-heart__dot2{transform:scale(0) translate(-60px,-5px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group7{opacity:1;transition:.1s all .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group7 .ani-heart__dot1{transform:scale(0) translate(-55px,-30px);transform-origin:0 0 0;transition:1.5s transform .3s}#checkbox:checked~.anicon-heart label .anicon-heart__group7 .ani-heart__dot2{transform:scale(0) translate(-30px,-15px);transform-origin:0 0 0;transition:.5s transform .3s}@keyframes animateCircle{40%{transform:scale(10);opacity:1;fill:var(--color-purple-300)}55%{transform:scale(11);opacity:1;fill:var(--color-purple-200)}65%{transform:scale(12);opacity:1;fill:var(--color-purple-300)}75%{transform:scale(13);opacity:1;fill:transparent;stroke-width:.5}85%{transform:scale(17);opacity:1;fill:transparent;stroke-width:.2}95%{transform:scale(18);opacity:1;fill:transparent;stroke-width:.1}100%{transform:scale(19);opacity:1;fill:transparent;stroke-width:0}}@keyframes animateHeartEnter{0%{transform:scale(.2)}40%{transform:scale(1.4)}100%{transform:scale(1)}}@keyframes animateHeartExit{50%{transform:scale(1.2)}100%{transform:scale(1)}}</style></head><body><div class=stars><div id=stars1></div><div id=stars2></div><div id=stars3></div></div><section class=content><input type=checkbox id=checkbox class=anicon-heart__checkbox><div class=text-container><h1 class=dating-request><GIRLFRIEND><br>quer namorar comigo?</h1><h2 class=love-message>Te amo, meu amor!</h2></div><div class=anicon-heart><label for=checkbox title=Sim!><svg id=heart-svg class=anicon-heart__svg viewBox=\"467 392 58 57\" xmlns=http://www.w3.org/2000/svg><g fill=none fill-rule=evenodd transform=\"translate(467 392)\"><path class=anicon-heart__heart d=\"M29.144 20.773c-.063-.13-4.227-8.67-11.44-2.59C7.63 28.795 28.94 43.256 29.143 43.394c.204-.138 21.513-14.6 11.44-25.213-7.214-6.08-11.377 2.46-11.44 2.59z\" fill=var(--color-neutral-100) /><circle class=anicon-heart__circ fill=var(--color-red-100) opacity=0 cx=29.5 cy=29.5 r=1.5 /><g class=anicon-heart__group1 opacity=0 transform=translate(24)><circle class=ani-heart__dot1 fill=var(--color-blue-100) cx=2 cy=3 r=2 /><circle class=ani-heart__dot2 fill=var(--color-blue-100) cx=7 cy=2 r=2 /></g><g class=anicon-heart__group2 opacity=0 transform=\"translate(44 6)\"><circle class=ani-heart__dot1 fill=var(--color-purple-100) cx=5 cy=6 r=2 /><circle class=ani-heart__dot2 fill=var(--color-purple-100) cx=2 cy=2 r=2 /></g><g class=anicon-heart__group3 opacity=0 transform=\"translate(52 28)\"><circle class=ani-heart__dot1 fill=var(--color-green-100) cx=2 cy=7 r=2 /><circle class=ani-heart__dot2 fill=var(--color-green-100) cx=4 cy=2 r=2 /></g><g class=anicon-heart__group4 opacity=0 transform=\"translate(35 50)\"><circle class=ani-heart__dot1 fill=var(--color-red-200) cx=6 cy=5 r=2 /><circle class=ani-heart__dot2 fill=var(--color-red-200) cx=2 cy=2 r=2 /></g><g class=anicon-heart__group5 opacity=0 transform=\"translate(14 50)\"><circle class=ani-heart__dot1 fill=var(--color-blue-100) cx=6 cy=5 r=2 /><circle class=ani-heart__dot2 fill=var(--color-blue-100) cx=2 cy=2 r=2 /></g><g class=anicon-heart__group6 opacity=0 transform=\"translate(0 28)\"><circle class=ani-heart__dot1 fill=var(--color-purple-200) cx=2 cy=7 r=2 /><circle class=ani-heart__dot2 fill=var(--color-purple-200) cx=3 cy=2 r=2 /></g><g class=anicon-heart__group7 opacity=0 transform=\"translate(7 6)\"><circle class=ani-heart__dot1 fill=var(--color-purple-300) cx=2 cy=6 r=2 /><circle class=ani-heart__dot2 fill=var(--color-purple-300) cx=5 cy=2 r=2 /></g></g></svg></label><p class=notice>Se <span>sim</span>, toque no coração.</p></div></section></body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }

  for (int i = 0; i < frames; i++) {
    delay(50);
    tft.pushImage((int)(DISPLAY_W - animation_width)/2, (DISPLAY_H - animation_height) / 2, animation_width, animation_height, heart[i]);
  }
}
