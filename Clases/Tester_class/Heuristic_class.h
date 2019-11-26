#ifndef PROYECT_1_HEURISTIC_CLASS_H
#define PROYECT_1_HEURISTIC_CLASS_H

class Heuristic_class{
private:
    string Name;
    int posX;
    int posY;
public:
    explicit Heuristic_class(string name, int posX, int posY) : Name(std::move(name)), posX(posX), posY(posY){}

    const string &getName() const {
        return Name;
    }

    int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
    }

    static double Calculate_weight(const Heuristic_class& id1,const Heuristic_class& id2){
        double x = id1.getPosX() - id2.getPosX();
        double y = id1.getPosY() - id2.getPosY();

        double result = sqrt( pow(x,2) + pow(y,2) );

        return result;
    }
    ~Heuristic_class()= default;

};


#endif //PROYECT_1_HEURISTIC_CLASS_H
