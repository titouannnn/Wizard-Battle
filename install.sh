#!/bin/sh

# Récupérer le chemin d'accès du répertoire où le script est exécuté
current_directory=$(dirname "$(readlink -f "$0")")

# Ajouter le chemin au LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$current_directory/src

# Afficher un message (facultatif)
echo "LD_LIBRARY_PATH a été mis à jour avec $current_directory/src"
