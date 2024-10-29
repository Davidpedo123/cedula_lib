from setuptools import setup, Extension

# Define el módulo de extensión
cedula_lib_module = Extension('cedula_lib',
                              sources=['consulta.c'] # Directorios de bibliotecas
                              )
                            

setup(name='cedula_lib',
      version='0.0.2',
      description='Módulo en C para formatear y consultar cédulas',
      ext_modules=[cedula_lib_module],  # Lista de módulos de extensión a compilar
      )
