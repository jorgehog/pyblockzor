qpwd=$1
qspwd=$2

pwd=$PWD

cd $qpwd
python setup.py build $qspwd/../lib --build-base=$qspwd/../build
cd $pwd
