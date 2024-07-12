from setuptools import setup, Extension

# Define el módulo de extensión
cedula_lib_module = Extension('cedula_lib',
                              sources=['consulta.c'],  # Lista de archivos fuente C
                              libraries=['curl'],  # Nombre de la biblioteca a vincular (sin prefijo 'lib' y sin extensión)
                              include_dirs=['C:/Users/etejada/OneDrive - INAFOCAM/Escritorio/Consejos/Prueba/Crecimiento personal/curl-8.8.0_3-win64a-mingw/include'],  # Directorio que contiene curl.h
                              library_dirs=['C:/Users/etejada/OneDrive - INAFOCAM/Escritorio/Consejos/Prueba/Crecimiento personal/curl-8.8.0_3-win64a-mingw/lib'],  # Directorios de bibliotecas
                              )
                            

setup(name='cedula_lib',
      version='0.0.2',
      description='Módulo en C para formatear y consultar cédulas',
      ext_modules=[cedula_lib_module],  # Lista de módulos de extensión a compilar
      )
