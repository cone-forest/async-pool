printf "import matplotlib.pyplot as plt\ndata = [0] * " > viz.py

./build/mr-async-pool-tests >> viz.py

printf "plt.plot(range(len(data)), data)\nplt.title('Acquisition rate')\nplt.xlabel('Object index')\nplt.ylabel('Times an object was acquired')\nplt.show()" >> viz.py

python viz.py
rm viz.py
