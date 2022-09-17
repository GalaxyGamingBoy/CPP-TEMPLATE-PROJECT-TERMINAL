#!/bin/sh
mkdir docs
GITREPO=https://github.com/GalaxyGamingBoy/CPP-TEMPLATE-PROJECT-TERMINAL
cd docs
git clone $GITREPO
cd CPP-TEMPLATE-PROJECT-TERMINAL
git checkout -b docs
mkdir web
mv docsRedirect.html index.html
git add *
git commit -m "chore: Update Doxygen Docs"
git push --force $GITREPO docs
cd ../..
rm -rf docs
