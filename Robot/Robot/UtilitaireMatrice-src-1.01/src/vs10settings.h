/* Specificites Visual Studio
 * FILE: vs10settings.h
 * AUTHOR: Guillaume Riviere (C) 2012  */

#ifndef VISUAL_STUDIO_10_SETTINGS
#define VISUAL_STUDIO_10_SETTINGS



/* La fonction round() doit etre definie   *
 * car elle n'est pas definie par le       *
 * compilateur C de Visual Studio          */
#define round(x) ((x-floor(x))>0.5 ? ceil(x) : floor(x))



/* Indiquer au compilateur d'ignorer les   *
 * depreciations emises par Visual Studio  *
 * pour les fonctions fopen(), fscanf(),   *
 * sprintf(), strcpy(), strdup(), etc.     */
#define _CRT_SECURE_NO_WARNINGS 1



#endif /* VISUAL_STUDIO_10_SETTINGS */
