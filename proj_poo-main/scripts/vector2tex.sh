#!/bin/bash

# Les étiquettes (labels) sont typographiées selon leur type :
# - "BLACK" : case noire
# - Commence par "COL" : somme de colonne
# - Commence par "ROW" : somme de ligne
# - Contient "BOTH" : somme ligne + colonne
# - nombre pour les cases avec les chiffres 


cat <<"EOF"
\documentclass[tikz]{standalone}  % Classe de document compacte pour générer uniquement le dessin
\usepackage{xstring}   % Pour manipuler les chaînes (tests, extractions)
\usetikzlibrary{calc} % Pour les calculs de position dans TikZ
\newcounter{COLOR}

% Définition de la macro \PLAIN qui dessine chaque cellule :
% Arguments :
%   #1 : position X
%   #2 : position Y
%   #3 : largeur
%   #4 : hauteur
%   #5 : étiquette de la cellule


\newcommand{\PLAIN}[5]{%
  \edef\CHECKLABEL{#5}  % On stocke le label dans une variable
  \def\BLACKLABEL{BLACK}% Étiquette spéciale pour les cases noires
  \def\GRIDEP{DEP}
  \def\SOLGRI{SOL}
  \def\EMPTY{EMPTY}


  % Si c'est une case noire
  \IfStrEq{\CHECKLABEL}{\GRIDEP}{%
    \colorlet{backcolor}{purple}        % bck red
    \def\textcolorlabel{\color{white}} % 
    \def\finalLabel{DEPART} % 
  }{%
    \IfStrEq{\CHECKLABEL}{\SOLGRI}{%
      \colorlet{backcolor}{blue}        % bck red
      \def\textcolorlabel{\color{white}} % 
      \def\finalLabel{SOLUTION} % 
    }{%
      \IfStrEq{\CHECKLABEL}{\BLACKLABEL}{%
        \colorlet{backcolor}{black}      % bck noir
        \def\textcolorlabel{\color{black}} % 
        \def\finalLabel{}                % 
      }{%
    \IfBeginWith{\CHECKLABEL}{COL}{   %   Si le label commence par "COL" (somme colonne)
      \colorlet{backcolor}{blue!40}   %   Fond bleu clair
      \def\textcolorlabel{\color{black}}%
      \def\finalLabel{\CHECKLABEL \textbackslash} % Exemple : COL25 devient "COL25\"
    }{%
      \IfBeginWith{\CHECKLABEL}{ROW}{     %    Si le label commence par "ROW" (somme ligne)
        \colorlet{backcolor}{red!40}       %     Fond rouge clair
        \def\textcolorlabel{\color{black}}%
        \def\finalLabel{\textbackslash \CHECKLABEL} % Exemple : ROW11 devient "\ROW11"
      }{
        \IfSubStr{\CHECKLABEL}{BOTH}{    %                Si le label contient "BOTH" (ligne + colonne)
          \StrBefore{\CHECKLABEL}{BOTH}[\FirstPart]   %   Partie avant BOTH
          \StrBehind{\CHECKLABEL}{BOTH}[\SecondPart]  %   Partie après BOTH
          \colorlet{backcolor}{cyan!40}               %   Fond cyan
          \def\textcolorlabel{\color{black}}          % Text 
          \def\finalLabel{\FirstPart \textbackslash \SecondPart} % Exemple : 5BOTH8 devient "5\8"
        }{
          \IfSubStr{\CHECKLABEL}{EMPTY}{
            \colorlet{backcolor}{white}      
            \def\textcolorlabel{\color{white}}
            \def\finalLabel{}
          }
          {
            \colorlet{backcolor}{white} %    Autre cas : cellule numérique classique
            \def\textcolorlabel{\color{black}}%
            \def\finalLabel{\CHECKLABEL}%
          }
        }
      }
    }
  }
  }}
  % Dessin de la cellule rectangle avec couleur de fond

  \path[draw=black,fill=backcolor]
  (#1,#2) coordinate(ul) rectangle ++(#3,#4) coordinate (lr);
  % Placement du texte au centre de la cellule
  % → font=\sffamily\Large\textcolorlabel :
  %    - \sffamily : police sans serif
  %    - \Large : taille du texte (plus grande que normale, voir ci-dessous)
  %    - \texttt : style monospacé (type machine à écrire)

  \path ($(ul)!0.5!(lr)$) node[overlay, font=\sffamily\Huge\textcolorlabel] {\texttt{\finalLabel}};%

}

\begin{document}
\begin{tikzpicture}[x=0.1cm,y=-0.1cm] % Début du dessin TikZ
EOF

# Traitement des lignes "vector" :
# Exemple de ligne d'entrée : 50:100:50:50:8
# Elle devient : \PLAIN{50}{100}{50}{50}{8}
sed -e 's/^/\\PLAIN{/' \
    -e 's/:/}{/g' \
    -e 's/$/}/'


# Fermeture du document LaTeX
cat <<"EOF"
\end{tikzpicture}
\end{document}
EOF
