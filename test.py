import time
import cedula_lib 


def benchmark_c(num_cedulas):
    cedulas = ['40233149323'] * num_cedulas  
    start_time = time.time()

    
    cedulas_list = [str(cedula) for cedula in cedulas]

    
    resultado = cedula_lib.formatear_cedula(cedulas_list)

    end_time = time.time()
    return end_time - start_time


def ajustar_cedula(cedula):
    cedula_sin_guion = str(cedula).replace("-", "").replace("_", "")
    if len(cedula_sin_guion) < 11:
        cedula_sin_guion = cedula_sin_guion.zfill(11)
    return "%s-%s-%s" % (cedula_sin_guion[0:3], cedula_sin_guion[3:10], cedula_sin_guion[-1])


def benchmark_python(num_cedulas):
    cedulas = ['40233149323'] * num_cedulas  
    start_time = time.time()

    for cedula in cedulas:
        resultado = ajustar_cedula(cedula)

    end_time = time.time()
    return end_time - start_time



num_cedulas = 1000000  
print(f'Numero de cedulas: {num_cedulas}')

tiempo_c = benchmark_c(num_cedulas)
tiempo_python = benchmark_python(num_cedulas)

print(f'Tiempo en C: {tiempo_c:.4f} segundos')
print(f'Tiempo en Python: {tiempo_python:.4f} segundos')
