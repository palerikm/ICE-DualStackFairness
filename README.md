HappyE-ICE-Test


Sample code to show how a simple algoritm can alter the
candidate priority to achive more fairnes for IPv4 candidates
in a dual-stack environment.

Please feel free to add more algorithms or tests.

Compiling
===============
Run ./bootstrap to create the configure script.

then do ./configure
and
 
make

Running
===============

There are two txt files with candidates. One with local candidates where priorities needs to be calculated and a predefined remote candidate file. (Please Note parsing is crude so keep the files clean..)

the program can bu run as follows:

src/icehetest 4 candidates.txt remoteCandidates.txt 

4 indicates the number of concecutive candidates if same address type allowed.

Have FUN!



Please see the ICE happy eyballs for more information
http://tools.ietf.org/html/draft-reddy-mmusic-ice-happy-eyeballs-05

<a href='https://travis-ci.org/palerikm/HappyE-ICE-Test'><img src='https://travis-ci.org/palerikm/HappyE-ICE-Test.png?branch=master'></a>
