# === Makefile ===

# Nombre del ejecutable final
TARGET = simulacion

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Archivos fuente
SRCS = main.cpp agua.cpp alimentos.cpp Exito.cpp refugio.cpp senales.cpp moral.cpp

# Archivos objeto (mismo nombre pero extensión .o)
OBJS = $(SRCS:.cpp=.o)

# Cabeceras (para dependencias)
HEADERS = definicion.hpp

# Regla por defecto
all: $(TARGET)

# Cómo crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla general para compilar .cpp a .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clear:
	rm -f $(OBJS) $(TARGET)

# Para recompilar desde cero
rebuild: clean all
