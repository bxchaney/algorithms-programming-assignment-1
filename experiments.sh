echo "filename,type,size,m,comparisons" > ./output.csv

mkdir -vp ./data/exp
# generate random datasets
python ./make_points.py 50 10000 > ./data/exp/dataset50_1.txt
python ./make_points.py 50 10000 > ./data/exp/dataset50_2.txt
python ./make_points.py 50 10000 > ./data/exp/dataset50_3.txt
python ./make_points.py 50 10000 > ./data/exp/dataset50_4.txt
python ./make_points.py 50 10000 > ./data/exp/dataset50_5.txt

python ./make_points.py 100 10000 > ./data/exp/dataset100_1.txt
python ./make_points.py 100 10000 > ./data/exp/dataset100_2.txt
python ./make_points.py 100 10000 > ./data/exp/dataset100_3.txt
python ./make_points.py 100 10000 > ./data/exp/dataset100_4.txt
python ./make_points.py 100 10000 > ./data/exp/dataset100_5.txt

python ./make_points.py 250 10000 > ./data/exp/dataset250_1.txt
python ./make_points.py 250 10000 > ./data/exp/dataset250_2.txt
python ./make_points.py 250 10000 > ./data/exp/dataset250_3.txt
python ./make_points.py 250 10000 > ./data/exp/dataset250_4.txt
python ./make_points.py 250 10000 > ./data/exp/dataset250_5.txt

python ./make_points.py 500 10000 > ./data/exp/dataset500_1.txt
python ./make_points.py 500 10000 > ./data/exp/dataset500_2.txt
python ./make_points.py 500 10000 > ./data/exp/dataset500_3.txt
python ./make_points.py 500 10000 > ./data/exp/dataset500_4.txt
python ./make_points.py 500 10000 > ./data/exp/dataset500_5.txt

python ./make_points.py 750 10000 > ./data/exp/dataset750_1.txt
python ./make_points.py 750 10000 > ./data/exp/dataset750_2.txt
python ./make_points.py 750 10000 > ./data/exp/dataset750_3.txt
python ./make_points.py 750 10000 > ./data/exp/dataset750_4.txt
python ./make_points.py 750 10000 > ./data/exp/dataset750_5.txt

python ./make_points.py 1000 10000 > ./data/exp/dataset1000_1.txt
python ./make_points.py 1000 10000 > ./data/exp/dataset1000_2.txt
python ./make_points.py 1000 10000 > ./data/exp/dataset1000_3.txt
python ./make_points.py 1000 10000 > ./data/exp/dataset1000_4.txt
python ./make_points.py 1000 10000 > ./data/exp/dataset1000_5.txt

python ./make_points.py 1250 10000 > ./data/exp/dataset1250_1.txt
python ./make_points.py 1250 10000 > ./data/exp/dataset1250_2.txt
python ./make_points.py 1250 10000 > ./data/exp/dataset1250_3.txt
python ./make_points.py 1250 10000 > ./data/exp/dataset1250_4.txt
python ./make_points.py 1250 10000 > ./data/exp/dataset1250_5.txt

python ./make_points.py 1500 10000 > ./data/exp/dataset1500_1.txt
python ./make_points.py 1500 10000 > ./data/exp/dataset1500_2.txt
python ./make_points.py 1500 10000 > ./data/exp/dataset1500_3.txt
python ./make_points.py 1500 10000 > ./data/exp/dataset1500_4.txt
python ./make_points.py 1500 10000 > ./data/exp/dataset1500_5.txt

python ./make_points.py 1750 10000 > ./data/exp/dataset1750_1.txt
python ./make_points.py 1750 10000 > ./data/exp/dataset1750_2.txt
python ./make_points.py 1750 10000 > ./data/exp/dataset1750_3.txt
python ./make_points.py 1750 10000 > ./data/exp/dataset1750_4.txt
python ./make_points.py 1750 10000 > ./data/exp/dataset1750_5.txt

python ./make_points.py 2000 10000 > ./data/exp/dataset2000_1.txt
python ./make_points.py 2000 10000 > ./data/exp/dataset2000_2.txt
python ./make_points.py 2000 10000 > ./data/exp/dataset2000_3.txt
python ./make_points.py 2000 10000 > ./data/exp/dataset2000_4.txt
python ./make_points.py 2000 10000 > ./data/exp/dataset2000_5.txt

# iterate through all files in ./data/exp directory
for file in ./data/exp/*;
    do 
    ./build/closest-pairs $file 5 0 >> ./output.csv;
    ./build/closest-pairs $file 5 1 >> ./output.csv;
    ./build/closest-pairs $file 10 0 >> ./output.csv;
    ./build/closest-pairs $file 10 1 >> ./output.csv;
    ./build/closest-pairs $file 20 0 >> ./output.csv;
    ./build/closest-pairs $file 20 1 >> ./output.csv;
    done