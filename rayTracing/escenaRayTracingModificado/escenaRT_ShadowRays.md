# Diferentes versiones de la obtencion de rayo de sombra

## Intento 1
//Falla
bool EscenaRayTracing::intento1esRayoDeSombra(Punto3D puntoInterseccion, Primitiva* p) {
    for (const auto& l : luces) {
        //cout << "Depurando: Para la primitiva de color: " << p->getColor()<< endl;
        Rayo rayoDeSombra = Rayo(puntoInterseccion, l->getCentro());
        float dPuntoLuz = (puntoInterseccion - l->getCentro()).modulus();
        bool haIntersectado = false;

        // Comprobamos si alguna primitiva bloquea el rayo hacia esta luz
        int Depurando = 0;
        for (const auto& pri : primitivas) {
            Interseccion inter = pri->interseccionRayo(rayoDeSombra);
            if (inter.intersecta){
                for(int i = 0; i < inter.puntoInterseccion.size(); i++){
                    if(puntoInterseccion != i){
                        if(puntoSobreRayo(puntoInterseccion, l->getCentro(), inter.puntoInterseccion[i])) {
                            if(Depurando < 10){
                                //cout << "Depurando: Punto de choque con primitiva de color: " << inter.colorPrimitiva << endl;
                            }
                            Depurando++;
                            // Si algun punto de interseccion esta sobre el rayo
                            // entre el origen del rayo de sombra y la luz ->
                            // esta a la sombra
                            haIntersectado = true;
                            break; // Salimos del bucle de primitivas para esta luz
                        }
                        else {
                            //cout << "Depurando - No ha intersectado con ninguna prim -> punto de luz" << endl;
                        }
                    }
                }
            }
        }

        if (!haIntersectado) {
            //cout << "Depurando - El punto esta en luz directa" << endl;
            return false; // El punto está en luz directa de al menos una luz
        }
    }
    // Si todas las luces están bloqueadas, el punto está en sombra
    return true;
}

## Intento 2
// Falla
RGB EscenaRayTracing::intento2esRayoDeSombra(Punto3D puntoInterseccion, Interseccion interseccion){
    for(auto l : luces){
        Direccion direccionRayo = l->getCentro() - puntoInterseccion;
        Rayo rayo = Rayo(puntoInterseccion, direccionRayo.normalize());
        Interseccion inter;

        inter.intersecta = false;
        float distancia = rayo.getDireccion().modulus();

        for(auto p : primitivas) {
            Interseccion i = p->interseccionRayo(rayo);
            if(i.intersecta){
                for(int j = 0; j < i.distancia.size(); j++){
                    if(i.distancia[j] < distancia && i.distancia[j] > 0){
                        // El punto esta en luz
                        //RGB colorEnLuz = l->getPotencia() / (rayo.getDireccion().dot_product(rayo.getDireccion()));
                        //float colorGeometria = abs(interseccion.normal.dot_product(rayo.getDireccion().normalize()));
                        //return colorEnLuz * colorGeometria;
                        return interseccion.colorPrimitiva;
                    }
                }
            }
        }
    }
    return RGB(0,0,0);
}

## Intento 3
// Falla
RGB EscenaRayTracing::intento3(Interseccion interseccion, Punto3D puntoInterseccion){
    bool puntoEnSombra = false;

    if(interseccion.intersecta){
        for(auto l : luces) {
            if(l->getTipo() == 0) { // Es luz puntual
                // Crear rayo desde la interseccion y la luz
                Rayo rayoSombra = Rayo(l->getCentro(), puntoInterseccion);

                // Ver si el rayo intersecta con alguna primitiva
                // ENTRE EL ORIGEN Y LA LUZ !!!
                for(auto p : primitivas) {
                    Interseccion interSombra = p->interseccionRayo(rayoSombra);

                    if(interSombra.intersecta) {
                        // El rayo ha intersectado con una primitiva

                        // Hay que comprobar que el punto causante de la
                        // interseccion no soy yo, ie, el punto a evaluar si esta o no en sombra

                        for(int i = 0; i < interSombra.puntoInterseccion.size(); i++){
                            // Me aseguro de que no soy yo
                            if(interSombra.puntoInterseccion[i] != puntoInterseccion){
                                // Si no soy yo -> entonces es posible que me este haciendo sombra.
                                // Debo asegurarme de que esta entre la luz y yo

                                if(puntoEnSegmento(puntoInterseccion, l->getCentro(), interSombra.puntoInterseccion[i])){
                                    // El punto esta en el segmento -> hace sombra
                                    puntoEnSombra = true;

                                    // Me guardo otros datos de interes
                                    
                                }
                            }
                        }
                    }
                }
            }

        }
        if(puntoEnSombra){
            return RGB(0,0,0);
        }
        else {
            return interseccion.colorPrimitiva;
        }
    }
}


## Ultima version de ShadowRays

PathTracing -> rayos de sombra
if(vectorIntersecciones.size() > 0) { //No vacio
    for(int l = 0; l < luces.size(); l++){
        bool enSombra = false;
        Punto3D centroLuz = luces[l]->getCentro();
        Punto3D origenRayoSombra = sumaPuntoDireccion(puntoMenorDistancia, (normalMenorDistancia.normalize()+DESPLAZAMIENTO));
        //cout << "Depurando: punto origen rayo sombra: P" << origenRayoSombra << endl;
        //cout << "Depurando: punto MenorDistanicia: P" << puntoMenorDistancia << endl;
        //cout << "Depurando: normal MenorDistanicia: N" << normalMenorDistancia << endl;
        //cout << "Depurando: normal.normalize() " << normalMenorDistancia.normalize() << endl;
        //cout << "Depurando: normal MenorDistanicia n*d: N*D" << (normalMenorDistancia.normalize()+DESPLAZAMIENTO) << endl;

        Rayo rayoSombra = Rayo(origenRayoSombra, centroLuz - origenRayoSombra);
        float distanciaLuz = (centroLuz - puntoMenorDistancia).modulus();
        //cout << "Depurando: Distancia luz " << distanciaLuz << endl;
        //cout << "Depurando: punto centroLuz: P" << centroLuz << endl;
        //cout << "Depurando: punto MenorDistanicia: P" << puntoMenorDistancia << endl;
        //cout << "Depurando: ------------------------------------------------" << endl;

        //cout << "Depurando: Direccion rayo sombra luz: D" << rayoSombra.getDireccion() << endl;
        //cout << "Depurando: NormalMenorDistancia: N " << rayoSombra.getDireccion() << endl;
        //cout << "Depurando: producto punto: " << rayoSombra.getDireccion().dot_product(normalMenorDistancia) << endl;
        

        /*
        // verificar si el rayo de sombra está orientado hacia el exterior de la superficie o hacia el interior
        if(primitivaEvaluada->getTipo() == "Esfera") { 
            // Parece que las normales estuvieran apuntando hacia dentro de ellas mismas??   
            // Esta condicion esta MAL 
            if(rayoSombra.getDireccion().dot_product(normalMenorDistancia) < 0) {
                enSombra = true;
            }
        }
        */
        // Si no se pone la condicion de las esferas, los planos IZQ, DCHO, Fondo y Techo salen en negro porque la normal esta en direccion opuesta al rayo de sombra ¿?
        // Cuando estan las dos condiciones descomentadas -> se ve el fondo completo pero no se ven las dos esferas (salen completamente en sombra)

        
        // Esto (que deberia generar las sombras bajo las esferas) crea una sombra extraña en la parte central superior del plano suelo
        for(int m = 0; m < primitivas.size() && !enSombra; m++) {
            Interseccion interseccionSombra = primitivas[m]->interseccionRayo(rayoSombra);
            if(interseccionSombra.intersecta) {
                float distanciaSombraMin = calcularMIN(interseccionSombra.distancia);
                if(distanciaSombraMin < distanciaLuz) {
                    enSombra = true;
                }
            }
        }
        

        if(!enSombra) {
            return colorPrimitiva;
        }
        else {
            return RGB(0,0,0);
        }
    }
}









# Version anterior de intersectarRayo

/*
RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo){
    
    vector<tuple<float, Punto3D>> distancia_Punto; 
    vector<Interseccion> interseccionesPrimitivas;
    vector<float> vectorDistancias;
    vector<Primitiva*> primitivasIntersectadas;

    for(const auto& pri : primitivas){
        Interseccion i = pri->interseccionRayo(rayo);
        if(i.intersecta){ // Si el rayo intersecta con alguna primitiva
            // Guardo la interseccion
            interseccionesPrimitivas.push_back(i);
            // Guardo la distancia minima
            float minDistancia = calcularMIN(i.distancia);
            vectorDistancias.push_back(minDistancia);
            
            Punto3D p = puntoInterseccionDadaDistancia(i, minDistancia);
            tuple<float, Punto3D> tupla(minDistancia, p); 
            distancia_Punto.push_back(tupla);



            //vectorDistancias.push_back(minDistancia);
            primitivasIntersectadas.push_back(pri);
        }
    }

    if(interseccionesPrimitivas.empty()){
        return colorPixel;
    }

    Primitiva* primitivaVisible;
    Interseccion interseccion;
    Punto3D puntoInterseccion;
    float menorDistancia = calcularMIN(vectorDistancias);
    
    for(int i = 0; i < interseccionesPrimitivas.size(); i++){
        for(int j = 0; j < interseccionesPrimitivas[i].distancia.size(); j++){
            if(interseccionesPrimitivas[i].distancia[j] == menorDistancia) {
                primitivaVisible = primitivasIntersectadas[i];
                interseccion = interseccionesPrimitivas[i];
                puntoInterseccion = interseccionesPrimitivas[i].puntoInterseccion[j];
            }
        }
    }

    // ShadowRays
    if(interseccion.intersecta){
        //return intento3(interseccion, puntoInterseccion);
        return interseccion.colorPrimitiva;
    }
    return colorPixel;
}
*/

## Ultima version de interseccion rayo:

// Interseccion rayo + rayos de sombra
RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo) {
    const float MAXIMA_DISTANCIA = 10000000.0F;
    const float DESPLAZAMIENTO = 0.000001F;

    vector<Interseccion> vectorIntersecciones;
    float menorDistancia = MAXIMA_DISTANCIA;
    int posInterseccion;
    Punto3D puntoMenorDistancia;
    Direccion normalMenorDistancia;
    RGB colorPrimitiva;
    Primitiva* primitivaEvaluada;

    // RayTracing -> Funciona bien
    for(int i = 0; i < primitivas.size(); i++){
        Interseccion interseccionPrimitiva = primitivas[i]->interseccionRayo(rayo);
        if(interseccionPrimitiva.intersecta) {
            vectorIntersecciones.push_back(interseccionPrimitiva);
            if(calcularMIN(interseccionPrimitiva.distancia) < menorDistancia){
                menorDistancia = calcularMIN(interseccionPrimitiva.distancia);
                puntoMenorDistancia = puntoInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                normalMenorDistancia = normalInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                posInterseccion = vectorIntersecciones.size()-1;
                colorPrimitiva = interseccionPrimitiva.colorPrimitiva;
                primitivaEvaluada = primitivas[i];
            }
        }
    }
 
    // PathTracing -> rayos de sombra
    if(vectorIntersecciones.size() > 0) { //No vacio
        for(int l = 0; l < luces.size(); l++){
            bool enSombra = false;
            Punto3D centroLuz = luces[l]->getCentro();
            Punto3D origenRayoSombra = sumaPuntoDireccion(puntoMenorDistancia, (normalMenorDistancia.normalize()+DESPLAZAMIENTO));
            //cout << "Depurando: punto origen rayo sombra: P" << origenRayoSombra << endl;
            //cout << "Depurando: punto MenorDistanicia: P" << puntoMenorDistancia << endl;
            //cout << "Depurando: normal MenorDistanicia: N" << normalMenorDistancia << endl;
            //cout << "Depurando: normal.normalize() " << normalMenorDistancia.normalize() << endl;
            //cout << "Depurando: normal MenorDistanicia n*d: N*D" << (normalMenorDistancia.normalize()+DESPLAZAMIENTO) << endl;

            Rayo rayoSombra = Rayo(origenRayoSombra, centroLuz - origenRayoSombra);
            float distanciaLuz = (centroLuz - puntoMenorDistancia).modulus();
            //cout << "Depurando: Distancia luz " << distanciaLuz << endl;
            //cout << "Depurando: punto centroLuz: P" << centroLuz << endl;
            //cout << "Depurando: punto MenorDistanicia: P" << puntoMenorDistancia << endl;
            //cout << "Depurando: ------------------------------------------------" << endl;

            //cout << "Depurando: Direccion rayo sombra luz: D" << rayoSombra.getDireccion() << endl;
            //cout << "Depurando: NormalMenorDistancia: N " << rayoSombra.getDireccion() << endl;
            //cout << "Depurando: producto punto: " << rayoSombra.getDireccion().dot_product(normalMenorDistancia) << endl;
            

            /*
            // verificar si el rayo de sombra está orientado hacia el exterior de la superficie o hacia el interior
            if(primitivaEvaluada->getTipo() == "Esfera") { 
                // Parece que las normales estuvieran apuntando hacia dentro de ellas mismas??   
                // Esta condicion esta MAL 
                if(rayoSombra.getDireccion().dot_product(normalMenorDistancia) < 0) {
                    enSombra = true;
                }
            }
            */
            // Si no se pone la condicion de las esferas, los planos IZQ, DCHO, Fondo y Techo salen en negro porque la normal esta en direccion opuesta al rayo de sombra ¿?
            // Cuando estan las dos condiciones descomentadas -> se ve el fondo completo pero no se ven las dos esferas (salen completamente en sombra)

            
            // Esto (que deberia generar las sombras bajo las esferas) crea una sombra extraña en la parte central superior del plano suelo
            for(int m = 0; m < primitivas.size() && !enSombra; m++) {
                Interseccion interseccionSombra = primitivas[m]->interseccionRayo(rayoSombra);
                if(interseccionSombra.intersecta) {
                    float distanciaSombraMin = calcularMIN(interseccionSombra.distancia);
                    if(distanciaSombraMin < distanciaLuz) {
                        enSombra = true;
                    }
                }
            }
            

            if(!enSombra) {
                return colorPrimitiva;
            }
            else {
                return RGB(0,0,0);
            }
        }
    }
    return colorPixel;
}