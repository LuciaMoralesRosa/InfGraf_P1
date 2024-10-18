# Variables
CXX = g++
CXXFLAGS = -Wall -g -I./geometria -I./geometria/primitivasGeometricas -I./imagen -I./rayTracing
LDFLAGS =

# Directorios
TESTDIR = tests
GEOMETRIADIR = geometria
PRIMITIVASDIR = $(GEOMETRIADIR)/primitivasGeometricas
IMAGENDIR = imagen
RAYTRACINGDIR = rayTracing
BUILDDIR = build

# Archivos fuente del proyecto
GEOMETRIA_SRCS = $(GEOMETRIADIR)/angulos.cpp $(GEOMETRIADIR)/coordenada.cpp $(GEOMETRIADIR)/direccion.cpp $(GEOMETRIADIR)/matriz4x4.cpp $(GEOMETRIADIR)/punto3d.cpp $(GEOMETRIADIR)/transformaciones.cpp

PRIMITIVAS_SRCS = $(PRIMITIVASDIR)/esfera.cpp $(PRIMITIVASDIR)/plano.cpp $(PRIMITIVASDIR)/triangulo.cpp

RAYTRACING_SRCS = $(RAYTRACINGDIR)/camara.cpp $(RAYTRACINGDIR)/color.cpp $(RAYTRACINGDIR)/pixel.cpp $(RAYTRACINGDIR)/rayo.cpp

SRCS = $(GEOMETRIA_SRCS) \ $(PRIMITIVAS_SRCS)  \ $(RAYTRACING_SRCS)

# Archivos objeto correspondientes
OBJS = $(SRCS:.cpp=.o)

# Tests disponibles
TESTS = camaratest

# Regla principal (compila todos los tests)
all: $(TESTS)

# Regla para compilar cada test de forma separada
$(TESTS): %: $(BUILDDIR)/%.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Regla para compilar los archivos fuente
$(GEOMETRIADIR)/%.o: $(GEOMETRIADIR)/%.cpp $(GEOMETRIADIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PRIMITIVASDIR)/%.o: $(PRIMITIVASDIR)/%.cpp $(PRIMITIVASDIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(IMAGENDIR)/%.o: $(IMAGENDIR)/%.cpp $(IMAGENDIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(RAYTRACINGDIR)/%.o: $(RAYTRACINGDIR)/%.cpp $(RAYTRACINGDIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar los tests
$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp $(TESTDIR)/%.hpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear el directorio build si no existe
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Limpiar archivos generados
clean:
	rm -f $(GEOMETRIADIR)/*.o $(PRIMITIVASDIR)/*.o $(IMAGENDIR)/*.o $(RAYTRACINGDIR)/*.o $(BUILDDIR)/*.o $(TESTS)

.PHONY: all clean
