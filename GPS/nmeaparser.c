#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCE_LENGTH 80

int main()
{
    char sentence[MAX_SENTENCE_LENGTH];
    char *token;

    printf("Enter NMEA sentence: ");
    fgets(sentence, MAX_SENTENCE_LENGTH, stdin);

    // Find $GPGLL sentence
    token = strtok(sentence, ",");
    while (token != NULL)
    {
        if (strcmp(token, "$GPGLL") == 0)
        {
            break;
        }
        token = strtok(NULL, ",");
    }

    // Extract latitude and longitude
    char *latitude = strtok(NULL, ",");
    char *ns = strtok(NULL, ",");
    char *longitude = strtok(NULL, ",");
    char *ew = strtok(NULL, ",");

    if (latitude == NULL || ns == NULL || longitude == NULL || ew == NULL)
    {
        printf("Invalid sentence\n");
        return 1;
    }

    // Convert latitude and longitude to decimal degrees
    double lat = atof(latitude) / 100;
    double lon = atof(longitude) / 100;
    lat += (atof(latitude) - lat * 100) / 60;
    lon += (atof(longitude) - lon * 100) / 60;
    if (*ns == 'S')
    {
        lat *= -1;
    }
    if (*ew == 'W')
    {
        lon *= -1;
    }

    // Print decimal degrees
    printf("Latitude: %lf, Longitude: %lf\n", lat, lon);

    // Print Google Maps link
    printf("Google Maps: https://www.google.com/maps/place/%lf,%lf\n", lat, lon);

    return 0;
}