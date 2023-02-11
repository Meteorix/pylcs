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
python -m build -s

py -m twine upload --repository pypi dist/*
