#! /bin/bash


CVSREPO=/home/nmwr/CVS;
cvswork=${CVSWORK-${HOME}/CVS-work}
MODULES=`$cvswork/configuration/scripts/modules-toplevel.sh`;

ALLROOT=GrAL
cd ${HOME}/tmp;
rm -rf ${ALLROOT};
mkdir ${ALLROOT};
cd ${ALLROOT};
for i in ${MODULES}
do
 cvs -d ${CVSREPO} export -r HEAD $i;
done;
mv gral/README .
mv gral/LICENSE .
mv gral/MODULES .
mv gral/INSTALL .
mv gral/Makefile.global ./Makefile

rm -rf configuration/scripts

# assume docs will be installed under ./doc
mv gral/index-global.html ./index.html 
perl -p -i -e 's|\$GRALDOC|doc|g' ./index.html


# insert license text in all sources
find . -name "*.h" -exec ${cvsroot}/configuration/scripts/replace-license.pl {} \;
find . -name "*.C" -exec ${cvsroot}/configuration/scripts/replace-license.pl {} \;


cd ..;
tar cf gral-all.tar ${ALLROOT};
gzip -f gral-all.tar;
rm -rf ${ALLROOT};

