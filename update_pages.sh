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

git clone -b gh-pages https://${GH_TOKEN}@github.com/palerikm/HappyE-ICE-Test.git deploy

mkdir deploy/dist_files

cp $DST_FILE deploy/dist_files
cd deploy

git add -A dist_files
git commit -m "Travis build $TRAVIS_BUILD_NUMBER pushed to gh-pages"
git push origin gh-pages

echo -e "Finishing to update gh-pages\n"



