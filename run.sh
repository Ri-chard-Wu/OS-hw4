
# Target=test_cancel
Target=test_cv

rm ${Target}

g++ -o ${Target} ${Target}.cpp -lpthread

./${Target}