@echo off
mkdir docs
set gitRepo=https://github.com/GalaxyGamingBoy/CPP-TEMPLATE-PROJECT-TERMINAL
cd docs
git clone %gitRepo%
cd CPP-TEMPLATE-PROJECT-TERMINAL
git checkout -b docs
doxygen
mkdir web
mv docsRedirect.html index.html
git add *
git commit -m "chore: Update Doxygen Docs"
git push --force %gitRepo% docs
cd ..\..
rm -rf docs