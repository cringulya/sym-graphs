with import <nixpkgs> { };

mkShell {
  nativeBuildInputs = with pkgs; [
    cmake
    ninja
    git
  ];

  shellHook = ''
    echo "Nix shell!"
  '';
}
