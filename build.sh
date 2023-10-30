#conda create -y -n py35 python=3.5 pybind11
#conda create -y -n py36 python=3.6 pybind11
#conda create -y -n py37 python=3.7 pybind11
#conda create -y -n py38 python=3.8 pybind11
#conda create -y -n py39 python=3.9 pybind11
#conda create -y -n py310 python=3.10 pybind11
#conda create -y -n py311 python=3.11 pybind11

conda activate py35
python -m pip install --upgrade build
python -m build -w
conda activate py36
python -m pip install --upgrade build
python -m build -w
conda activate py37
python -m pip install --upgrade build
python -m build -w
conda activate py38
python -m pip install --upgrade build
python -m build -w
conda activate py39
python -m pip install --upgrade build
python -m build -w
conda activate py310
python -m pip install --upgrade build
python -m build -w
conda activate py311
python -m pip install --upgrade build
python -m build -w
python -m build -s

py -m twine upload --repository pypi dist/*
