#/bin/sh

echo -e "Starting to update gh-pages\n"

make dist

for FILE in `ls *.tar.gz`
do
    NAME=$(echo "$FILE" | sed 's/\-[^\-]*$//')
    DST_FILE=$NAME-[build$TRAVIS_BUILD_NUMBER].tar.gz    
    mv $FILE $DST_FILE 
done

git config --global user.email "travis@travis-ci.org"
git config --global user.name "Travis"

git checkout gh-pages
mkdir deploy
cp $DST_FILE deploy
cd deploy

git add -A
git commit -m "Travis build $TRAVIS_BUILD_NUMBER pushed to gh-pages"
git push origin gh-pages

echo -e "Finishing to update gh-pages\n"



