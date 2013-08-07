f = open('main_h.tex','w')
f.write("""\documentclass[a4paper,5pt,twocolumn,titlepage]{article}

    
\usepackage{mathpazo}
\usepackage{xeCJK}
\usepackage{pstricks,pst-node,pst-tree}
    
%\setsansfont{Inconsolata}
%\setsansfont{DejaVu Sans Mono}
\setsansfont{Source Code Pro}
%\setsansfont{Monaco}

\setCJKmainfont{SimHei}
\setCJKsansfont{SimHei}
\setCJKmonofont{SimHei}

\usepackage{graphicx}
\usepackage{amsmath}
\usepackage{xcolor}
\usepackage{type1cm}
\usepackage{booktabs}
\usepackage{geometry}
%\usepackage[landscape]{geometry}
\geometry{left=1cm,right=1cm,top=1.5cm,bottom=1cm,headsep=0.2cm}

\usepackage{courier}
%\usepackage{time}
%\usepackage{charter}

\usepackage{fancyhdr}

\usepackage{listings}

\lstset{
breaklines=true,
tabsize=2,
numbers=left,
basicstyle=\\tiny\\ttfamily,
frame=leftline,
escapeinside=``,
extendedchars=false
}
\usepackage[CJKbookmarks=true,
colorlinks,
linkcolor=black,
anchorcolor=black,
citecolor=black]{hyperref}
\AtBeginDvi{\special{pdf:tounicode UTF8-UCS2}}

\usepackage{indentfirst}
\setlength{\parindent}{0em}


\\newcommand*{\TitleFont}{%
\\fontsize{50}{80}%
\\selectfont}
\\usepackage{graphicx}
\\title{\TitleFont{Code Library short}
\\begin{center}
\includegraphics[scale=2]{./image1.png}
\end{center}
}
\\author{Himemiya Nanao @ Perfect Freeze}

\\begin{document}
\maketitle \\tableofcontents
\\newpage
\pagenumbering{arabic}

""")

import os
for x,y,z in os.walk('.'):
	if x == '.':
		continue
	f.write('\section{'+x[2:]+'}\n')
	for files in z:
		if ((files == '.ds_store') or (files == '.DS_Store') or (files.endswith('~')) or files.endswith('.pdf')):
			continue
		ot=files
		if ot.endswith(""".cpp"""):
		    ot=ot.rstrip(""".cpp""")
		elif ot.endswith(""".cxx"""):
		    ot=ot.rstrip(""".cxx""")
		elif ot.endswith("""java"""):
		    ot="java"
		f.write('\subsection{'+ot+'}\n')
		fname = x+'/'+files
		fname = fname.lower()
		if files.count('.')!=0:
			if fname.endswith(""".java"""):
				lang = """Java"""
			else:
				lang = """C++"""
			f.write('\\lstinputlisting[language='+lang+']{\"'+fname+'\"}\n')
#			print files.count('.')
#			print files
		else:
			f.write('\\lstinputlisting{\"'+fname+'\"}\n')
f.write(
"""
\end{document}
""")
f.close()
