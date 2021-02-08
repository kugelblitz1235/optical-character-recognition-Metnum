# Reconocimiento de dígitos: Métodos Numéricos

## Instrucciones


1. Crear un repo git en donde se bajen esto

```
git init
git remote add origin <nuestra-nueva-url-de-git>
```

2. Bajarse los repositorios de `pybind` y `eigen` como submódulos

```
git submodule init
git submodule add https://github.com/eigenteam/eigen-git-mirror
git submodule add https://github.com/pybind/pybind11
git mv eigen-git-mirror eigen
# Elegimos versiones de eigen y pybind
cd pybind11/ && git checkout v2.2.4 && cd ..
cd eigen && git checkout 3.3.7 && cd ..
```

3. Instalar requerimientos

```
pip install -r requirements.txt
```

4. Descomprimir datos

```
cd data && gunzip *.gz && cd ..
```

5. Correr Jupyter

```
jupyter lab
```

### Datos

En `data/` tenemos los datos de entrenamiento (`data/train.csv`) y los de test (`data/test.csv`).


## Creación de un entorno virtual de python

### Con pyenv

```
curl https://pyenv.run | bash
```

Luego, se sugiere agregar unas líneas al bashrc. Hacer eso, **REINICIAR LA CONSOLA** y luego...

```
pyenv install 3.6.5
pyenv global 3.6.5
pyenv virtualenv 3.6.5 ocr
```

En el directorio del proyecto

```
pyenv activate ocr
```

### Directamente con python3
```
python3 -m venv ocr
source ocr/bin/activate
```

### Con Conda
```
conda create --name ocr python=3.6.5
conda activate ocr
```

## Instalación de las depencias
```
pip install -r requirements.txt
```

## Correr notebooks de jupyter

```
cd notebooks
jupyter lab
```
o  notebook
```
jupyter notebook
```


## Compilación
Ejecutar la primera celda del notebook `knn.ipynb` o seguir los siguientes pasos:


- Compilar el código C++ en un módulo de python
```
mkdir build
cd build
rm -rf *
cmake -DPYTHON_EXECUTABLE="$(which python)" -DCMAKE_BUILD_TYPE=Release ..
```
- Al ejecutar el siguiente comando se compila e instala la librería en el directorio `notebooks`
```
make install
```
cd .. && mkdir build
cd ../build/ && rm -rf *
cd ../build && cmake \
  -DPYTHON_EXECUTABLE="$(which python)" \
  -DCMAKE_BUILD_TYPE=Release ..
cd ../build && make install
