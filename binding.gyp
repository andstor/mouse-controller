{
    "targets": [{
        "target_name": "<(module_name)",
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/mouse_wrap.cpp",
        ],
        "conditions": [
            ['OS=="mac"', {
                'cflags+': ['-fvisibility=hidden'],
                'xcode_settings': {
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
                },
                'link_settings': {
                    'libraries': [
                        '$(SDKROOT)/System/Library/Frameworks/CoreGraphics.framework',
                        '$(SDKROOT)/System/Library/Frameworks/CoreFoundation.framework',
                    ]
                },
                "sources": [
                    "cppsrc/mouse.cpp",
                ],
            }],
        ],
        'defines': [
            'NAPI_DISABLE_CPP_EXCEPTIONS',
            "NAPI_VERSION=<(napi_build_version)",
        ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    }]
}
