# InfGraf_P1
Practicas de la asignatura Informatica Grafica 2024


Faltan ->
- rayos de sombra
- contribucion de la luz en escenaRayTracing en caso de que la luz no este a oscuras
- implementacion de pathTracer recursivo

## Repartido en sesiones
- Sesion 4 -> HECHO
Definicion de primitivas
DEfinicion de Rayo
Funciones de interseccion

- Sesion 5 -> HECHO
HECHO - RayTracing basico
HECHO - Creacion de camara
HECHO - Rayos desde camara a pixeles

- Sesion 6 -> FALLA
HECHO - Luces puntuales
FALLA - Rayos de sombra
HECHO - Implementacion de la funcion de evaluacion (difusa, especular y refractante) -> HECHO
FALTA - Calculo de la contribucion de la luz si no esta a la sombra -> FALLA (no implementado aunque es "facil")
        - tuplaDirRGB  dir, rgbEval = muestreo(...)
        - potPorDist = (luces[l]->potencia[0]/pow(distanciaLuz, 2))
        - coseno(n_omegao) = abs(vectorIntersecciones[posMin].normal*
                            ((luces[l]->centro-vectorIntersecciones[posMin].punto
                            /distanciaLuz)));
        - mediaColor[0] += porPorDist * rgb * coseno(n_omegao)

- Sesion 7 -> FALTA
HECHO (Sin probar) - Muestreo para medios difusos (tambien especulares y refractantes) -> muestreo del angulo solido uniforme
FALTA - Recursividad para nRayos (esta medio implementado de la primera opcion en Escena pero no me fio)

- Sesion 8 -> HECHO (no probado)
HECHO - Expansion de las funciones de evaluacion y de muestreo

# Preguntas:
1. Tema shadowRays


## Temas a resolver
1. Para materiales refractantes, ver como meter el medio de entrada y el medio de salida
