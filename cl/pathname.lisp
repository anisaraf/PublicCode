(in-package :com.gigamonkeys.pathnames)

(defvar home-dir "/Users/asaraf/")
(directory (make-pathname :name :wild :type :wild :defaults home-dir))