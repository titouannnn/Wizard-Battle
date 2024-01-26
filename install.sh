#!/bin/bash

# Récupérer le chemin d'accès du répertoire où le script est exécuté
current_directory=$(dirname "$(readlink -f "$0")")

# Export dans la variable d'environnement 
export LD_LIBRARY_PATH=$current_directory/lib:$LD_LIBRARY_PATH

# Ajouter la ligne au fichier .bashrc
ld_library_path_line="LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:$current_directory/lib"
if ! grep -q "$ld_library_path_line" "$HOME/.bashrc"; then
    echo "$ld_library_path_line" >> "$HOME/.bashrc"
    echo "La variable LD_LIBRARY_PATH a été ajoutée au fichier .bashrc avec le chemin $current_directory/lib"
else
    echo "La variable LD_LIBRARY_PATH est déjà configurée dans le fichier .bashrc"
fi

# Actualiser le fichier .bashrc
source "$HOME/.bashrc"

# Afficher un message (facultatif)
echo "LD_LIBRARY_PATH a été mis à jour avec $current_directory/lib"
