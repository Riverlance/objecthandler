/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef APP_H
#define APP_H

class GApp
{
  public:
    // Initialize variables
    GApp();

    // Deallocate memory
    ~GApp();

    // Prevent clone this object
    GApp(const GApp&) = delete; // Prevent construction by copying
    GApp& operator=(const GApp&) = delete; // Prevent assignment



    bool init(int argc, char* argv[]);



    /**
      * Singleton implementation.
      *
      * @return a SDL window handler singleton
      */
    static GApp* getInstance()
    {
      static GApp instance;
      return &instance;
    };

    bool isInitialized() { return initialized; }



  private:
    bool initialized;
};

#endif
