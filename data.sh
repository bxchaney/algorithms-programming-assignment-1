mkdir -vp data
python ./make_points.py 100 65535 > ./data/dataset1.txt
python ./make_points.py 1000 65535 > ./data/dataset2.txt
python ./make_points.py 10000 65535 > ./data/dataset3.txt
python ./make_points.py 100000 65535 > ./data/dataset4.txt
python ./make_points.py 1000000 65535 > ./data/dataset5.txt
