mkdir -vp data
python ./make_points.py 10 10 > ./data/dataset0.txt
python ./make_points.py 100 10000 > ./data/dataset1.txt
python ./make_points.py 1000 10000 > ./data/dataset2.txt
python ./make_points.py 10000 10000 > ./data/dataset3.txt
python ./make_points.py 100000 10000 > ./data/dataset4.txt
python ./make_points.py 1000000 10000 > ./data/dataset5.txt
