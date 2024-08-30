#ifndef CONFIG_HPP
#define CONFIG_HPP

class Config {
public:
    // Static instance method for singleton pattern
    static Config& instance() {
        static Config instance;
        return instance;
    }

    // Getters and setters for configurable constants
    double getPI() const { return PI; }
    void setPI(double value) { PI = value; }

    double getEpsilonMergeVertices() const { return EpsilonMergeVertices; }
    void setEpsilonMergeVertices(double value) { EpsilonMergeVertices = value; }

    double getSmoothFactor() const {return SmoothFactor;}
    void setSmoothFactor(double value) {SmoothFactor = value;}

    double getEpsilonIntersectsVectors() const {return EpsilonIntersectsVectors;}
    void setEpsilonIntersectsVectors(double value) {EpsilonIntersectsVectors = value;}

private:
    // Private constructor for singleton pattern
    Config() : PI(3.141592653589793),
    EpsilonMergeVertices(1e-5),
    SmoothFactor(0.5),
    EpsilonIntersectsVectors(1e-5) {}

    // Variables to hold the constant values
    double PI;
    double EpsilonMergeVertices;
    double EpsilonIntersectsVectors;
    double SmoothFactor;

    // Delete copy constructor and assignment operator
    Config(const Config&) = delete;
    void operator=(const Config&) = delete;
};

#endif // CONFIG_HPP
