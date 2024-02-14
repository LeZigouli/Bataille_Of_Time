/**
 * \file ordinateur.c
 * \brief Contient les fonction permettant à l'ordinateur de jouer.
 * \author Roquain Louison
 * \date 09 févrirer 2024
 * 
 * 
*/
#include "../lib/ordinateur.h"

/* fonction pour creer le batiment d'un joueur */
booleen_t init_building_or(ordi_t ** ordi)
{
	/* verification préliminaire */
	if ( (*ordi) == NULL || ordi == NULL )
	{
		return FALSE;
	}

	/* allocation dynamique */
	(*ordi)->building = malloc(sizeof(building_t));

	if ( (*ordi)->building == NULL )
	{
		printf("ERREUR : allocation building !\n");
		return FALSE;
	}

	/* affectation */
	(*ordi)->building->dammage = 33;
	(*ordi)->building->GOLD_cost = 500;
	(*ordi)->building->level = 1;
	(*ordi)->building->pv = 300;
	(*ordi)->building->max_pv = (*ordi)->building->pv;
	(*ordi)->building->owner = (*ordi)->owner;

	return TRUE;
}

ordi_t * init_ordi(int difficulte){
    ordi_t * ordi=malloc(sizeof(ordi_t));
    ordi->owner=OWNER_2;
    init_building_or(&ordi);
    ordi->characters=malloc(sizeof(tab_charactere_t)*MAX_POSSESSED);
    ordi->characters->nb=0;
    return ordi;
}

int detr_ordi(ordi_t ** ordi){
    free((*ordi)->building);
    if((*ordi)->characters!=NULL)
        free((*ordi)->characters->tab);
    free(*ordi);
    *ordi=NULL;
    return 0;
}

int envoie_char(ordi_t ** ordi,age_t current , character_t * tab[]){
    character_t * new;
    new=malloc(sizeof(character_t));
    if(new==NULL){
        printf("Looooooooooooooooooooooooooooooooool");
    }
    int newCha;
    if((*ordi)->characters->nb < MAX_POSSESSED){
        srand(time(NULL));
        newCha=rand()%NB_CHARACTER;
        copie_character(&new,tab[current*NB_CHARACTER+newCha]);
        (*ordi)->characters->tab[(*ordi)->characters->nb]=new;
        (*ordi)->characters->nb++;
    }
    return 0;
}

booleen_t afficher_building_or(ordi_t * ordi)
{
    if ( ordi == NULL )
    {
        return FALSE;
    }

    printf("<----- building ----->\n");
    printf("Owner : %d \nDammage : %d\nPV : %d\nGOLD_cost : %d\nLevel : %d\n",ordi->building->owner, ordi->building->dammage,ordi->building->pv, ordi->building->GOLD_cost, ordi->building->level);
    printf("<-------------------->\n\n");

    return TRUE;
}

void afficher_ordi(ordi_t * ordi){
    int i;
    printf("{\n");
    printf("Troupe :\n{");
    if(ordi->characters!=NULL){
        for(i=0;i<ordi->characters->nb;i++){
            if(ordi->characters->tab[i]!=NULL){
                printf("{");
                printf("pv: %d\nnom: %s\ntemps: %d\n",ordi->characters->tab[i]->pv,ordi->characters->tab[i]->name,ordi->characters->tab[i]->time);
                printf("}");
            }
        }
    }
    printf("}\n");
    afficher_building_or(ordi);
    printf("}\n");
}